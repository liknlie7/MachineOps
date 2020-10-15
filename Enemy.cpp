#include "pch.h"

#include "Enemy.h"
#include "Player.h"

// 通常の大きさ
const float Enemy::SIZE = 1.5f;

// ボスの大きさ
const float Enemy::BOSS_SIZE = 8.0f;

// コンストラクタ
Enemy::Enemy(const EnemyData _enemyData)
	: m_blinkTime(30)
	, m_isValid(false)
	, m_playerPos(0.0f, 0.0f, 0.0f)
	, m_wayNum(3)
	, m_changeAngle(30)
	, m_bulletEndAngle(0)
	, m_shotInterval(10.0f)
	, m_shotRotate(0.0f)
{
	m_enemyType = _enemyData.enemyType;
	m_maxLife = m_life =  _enemyData.life;
	m_speed = _enemyData.moveSpeed;
	m_collider.radius = _enemyData.collider;
	m_shotType = _enemyData.shotType;
}

void Enemy::Initialize(DirectX::SimpleMath::Vector3 _pos, DirectX::GeometricPrimitive* _bulletGeometry)
{
	// 弾の形状作成
	//m_pBulletGeometric = DirectX::GeometricPrimitive::CreateSphere(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(), 0.3f);

	switch (m_enemyType)
	{
	case NORMAL_ENEMY: // ノーマルタイプ

		m_position = _pos;

		m_collider.center = m_position;

		break;

		// 盾持ち
	case SHIELD_ENEMY:

		m_position = _pos;
		m_collider.center = m_position;
		m_shotType = 4;

		break;

	case BOSS_ENEMY:

		// エネミーモデルのshared_ptrを受け取る
		m_pEnemy = std::weak_ptr<DirectX::Model>(ResourceManager::GetInstance()->GetModel(L"Resources/Models/Enemy1.cmo"));

		m_position = _pos;
		m_collider.center = m_position;

		break;
	}

}

// 更新
void Enemy::Update()
{
	DirectX::SimpleMath::Vector3 m_dir;
	m_dir = m_playerPos - m_position;
	m_dir.Normalize();
	m_enemyAngle = atan2(m_dir.x, m_dir.z);

	switch (m_enemyType)
	{
	case NORMAL_ENEMY:

		ChasePlayer(m_playerPos);

		m_bulletEndAngle -= 180 + m_wayNum / 2 * m_changeAngle;

		for (int i = 0; i < m_wayNum; i++)
		{
			CreateBullet();
		}

		break;
	case SHIELD_ENEMY:

		break;
	case BOSS_ENEMY:

		ChasePlayer(m_playerPos);

		m_playerPos.Normalize();
		DirectX::SimpleMath::Vector3 baseDir = m_playerPos;


		break;
	}

	if (m_life <= 70 && m_life > 40)
		m_shotType = WHORL_SHOT;
	if (m_life <= 40)
		m_shotType = ALL_DIRECTION_SHOT;

	m_shotInterval++;
	switch (m_shotType)
	{
	case NORMAL_SHOT:
	{
		if (m_shotInterval > 15.0f)
		{
			m_pBulletManager->Shot(m_position, 0.15f, m_enemyAngle,m_pBulletManager->GetBulletGeometry(BulletManager::SPHERE));
			//m_pBullets.push_back(std::make_unique<Bullet>(m_position + DirectX::SimpleMath::Vector3(0.0f, 0.1f, 0.0f), DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.15f), m_enemyAngle));
			//CreateBullet();
			m_shotInterval = 0;

			break;
		}
	}
	case ALL_DIRECTION_SHOT:
	{
		if (m_shotInterval > 50.0f)
		{
			for (int rad = 0; rad < 130; rad += 6)
			{
				m_pBulletManager->Shot(m_position, 0.15f, (float)rad + m_enemyAngle, m_pBulletManager->GetBulletGeometry(BulletManager::SPHERE));
				//m_pBullets.push_back(std::make_unique<Bullet>(m_position + DirectX::SimpleMath::Vector3(0.0f, 0.1f, 0.0f), DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.15f), (float)rad + m_enemyAngle));
				//CreateBullet();
				m_shotInterval = 0;
			}
		}
		break;
	}
	case WHORL_SHOT:
		if (m_shotInterval > 10.0f)
		{

			int i = 0;
			while (i < 5)
			{
				m_pBulletManager->Shot(m_position, 0.15f, m_shotRotate, m_pBulletManager->GetBulletGeometry(BulletManager::SPHERE));
				//m_pBullets.push_back(std::make_unique<Bullet>(m_position + DirectX::SimpleMath::Vector3(0.0f, 0.1f, 0.0f), DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.15f), m_shotRotate));
				//CreateBullet();
				m_shotRotate += 0.2f;
				m_shotInterval = 0;
				i++;
			}
		}
		break;
	default:
		break;
	}
	// 速度代入
	m_position += m_velocity;

	//for (std::vector<std::unique_ptr<Bullet>>::iterator itr = m_pBullets.begin(); itr != m_pBullets.end(); itr++)
	//{
	//	(*itr)->Update();
	//}


	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateRotationY(m_enemyAngle);
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(BOSS_SIZE);
	m_matrix = scale * rotate * DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(m_position.x, 1.0f, m_position.z));

	m_collider.center = m_position;

	//if (m_life == 0)
	//	m_pEnemy = nullptr;

	//OutRangeBullet();
	if (m_isValid)  Blink();

}


// 描画
void Enemy::Render(const DirectX::SimpleMath::Matrix& _view)
{
	ID3D11DeviceContext1* context = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	DirectX::CommonStates* state = GameContext::Get<DirectX::CommonStates>();
	DirectX::SimpleMath::Matrix proj = GameContext::Get<Projection>()->GetMatrix();

	// モデル描画
	if (m_blinkTime % 5 == 0)
	{
		if (m_life != 0)
		{
			if (std::shared_ptr<DirectX::Model> sptr = m_pEnemy.lock())
			{
				sptr->Draw(context, *state, m_matrix, _view, proj);
			}
		}
	}

	// 弾描画
	//for (std::vector<std::unique_ptr<Bullet>>::iterator itr = m_pBullets.begin(); itr != m_pBullets.end(); itr++)
	//{
	//	(*itr)->Render(_view);
	//}
}

// 後始末
void Enemy::Finalize()
{

}

// プレイヤーを追いかける
void Enemy::ChasePlayer(DirectX::SimpleMath::Vector3 _playerPos)
{
	// プレイヤーへの向きを計算
	DirectX::SimpleMath::Vector3 dir = _playerPos - m_position;
	dir.Normalize();

	// エネミーの移動
	m_position += dir * m_speed;
}

// 点滅
void Enemy::Blink()
{
	m_blinkTime--;

	if (m_blinkTime < 0)
	{
		m_isValid = false;
		m_blinkTime = 30;
	}
}

// 衝突した時
void Enemy::OnCollision()
{
	m_life--;

	m_isValid = true;
}

// 弾の作成
void Enemy::CreateBullet()
{
	//for (std::vector<std::unique_ptr<Bullet>>::iterator itr = m_pBullets.begin(); itr != m_pBullets.end(); itr++)
	//{
	//	(*itr)->Initialize(m_pBulletGeometric.get());
	//}
}

// 弾が衝突した時
//void Enemy::BulletOnCollision(int _number)
//{
//	m_pBullets[_number]->SetIsValid(false);
//
//	std::vector<std::unique_ptr<Bullet>>::iterator itr = m_pBullets.begin();
//	while (itr != m_pBullets.end())
//	{
//		if (!(*itr)->GetIsValid())
//			itr = m_pBullets.erase(itr);
//		else
//			++itr;
//	}
//}

// 範囲外に出たら
//void Enemy::OutRangeBullet()
//{
//	std::vector<std::unique_ptr<Bullet>>::iterator itr = m_pBullets.begin();
//
//	while (itr != m_pBullets.end())
//	{
//		if ((*itr)->GetLife() < 0.0f)
//			itr = m_pBullets.erase(itr);
//		else
//			++itr;
//	}
//}