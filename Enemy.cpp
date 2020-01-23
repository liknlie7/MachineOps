#include "pch.h"

#include "Enemy.h"
#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using namespace std;

// 通常の大きさ
const float Enemy::SIZE = 1.5f;

// ボスの大きさ
const float Enemy::BOSS_SIZE = 8.0f;

// コンストラクタ
Enemy::Enemy(const int _type, const std::string& _tag)
	: GameObject(_tag)
	, m_blinkTime(30)
	, m_isValid(false)
	, m_playerPos(0.0f, 0.0f, 0.0f)
	, m_life(100)
	, m_maxLife(100)
	, m_wayNum(3)
	, m_changeAngle(30)
	, m_bulletEndAngle(0)
	, m_shotInterval(10.0f)
	, m_shotRotate(0.0f)
{
	m_enemyType = _type;
}

// デストラクタ
Enemy::~Enemy()
{
}

void Enemy::Initialize(DirectX::SimpleMath::Vector3 _pos)
{

	// エフェクトファクトリの作成 
	EffectFactory* factory = new EffectFactory(GameContext::Get<DX::DeviceResources>()->GetD3DDevice());

	// 弾の形状作成
	m_pBulletGeometric = GeometricPrimitive::CreateSphere(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(), 0.3f);

	// テクスチャの読み込みパス指定 
	factory->SetDirectory(L"Resources/Models");

	switch (m_enemyType)
	{

	case NORMAL_ENEMY: // ノーマルタイプ

		// モデルデータ読み込み 
		m_pEnemy = Model::CreateFromCMO(
			GameContext::Get<DX::DeviceResources>()->GetD3DDevice(),
			L"Resources/Models/Enemy1.cmo",
			*factory
		);
		delete factory;

		m_position = _pos;
		// 速さの初期化
		m_speed = 0.08f;

		m_life = 300;

		m_collider.radius = 2.0f;
		m_collider.center = m_position;
		//m_decisionAreaPos = m_pos;

		m_shotType = NORMAL_SHOT;
		break;

		// 盾持ち
	case SHIELD_ENEMY:

		// モデルデータ読み込み 
		m_pEnemy = Model::CreateFromCMO(
			GameContext::Get<DX::DeviceResources>()->GetD3DDevice(),
			L"Resources/Models/Enemy2.cmo",
			*factory
		);
		delete factory;

		m_position = _pos;
		// 速さの初期化
		m_speed = 0.05f;

		m_life = 5;

		m_collider.radius = 2.0f;
		m_collider.center = m_position;
		//m_decisionAreaPos = m_pos;
		m_shotType = 4;

		break;

	case BOSS_ENEMY:
		// モデルデータ読み込み 
		m_pEnemy = Model::CreateFromCMO(
			GameContext::Get<DX::DeviceResources>()->GetD3DDevice(),
			L"Resources/Models/Enemy1.cmo",
			*factory
		);
		delete factory;

		m_position = _pos;
		// 速さの初期化
		m_speed = 0.08f;

		m_life = m_maxLife;
		m_shotType = NORMAL_SHOT;
		m_collider.radius = /*2.0f*/5.0f;
		m_collider.center = m_position;
		//m_decisionAreaPos = m_pos;

		break;
	}

}

// 更新
void Enemy::Update()
{
	Vector3 m_dir;
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



		m_playerPos.Normalize();
		Vector3 baseDir = m_playerPos;


		break;
	}

	if (m_life <= 80 && m_life > 50)
		m_shotType = WHORL_SHOT;
	if (m_life <= 50)
		m_shotType = ALL_DIRECTION_SHOT;

	m_shotInterval++;
	switch (m_shotType)
	{
	case NORMAL_SHOT:
	{
		if (m_shotInterval > 15.0f)
		{
			m_pBullets.push_back(make_unique<Bullet>(m_position + Vector3(0.0f, 0.1f, 0.0f), m_enemyAngle, Vector3(0.0f, 0.0f, 0.15f), "EnemyBullet"));
			CreateBullet();
			m_shotInterval = 0;

			break;
		}
	}
	case ALL_DIRECTION_SHOT:
	{
		if (m_shotInterval > 15.0f)
		{
			for (int rad = 0; rad < 130; rad += 6)
			{
				m_pBullets.push_back(make_unique<Bullet>(m_position + Vector3(0.0f, 0.1f, 0.0f), (float)rad + m_enemyAngle, Vector3(0.0f, 0.0f, 0.15f), "EnemyBullet"));
				CreateBullet();
				m_shotInterval = 0;
			}
		}
		break;
	}
	case WHORL_SHOT:
		if (m_shotInterval > 5.0f)
		{

			int i = 0;
			while (i < 5)
			{
				m_pBullets.push_back(make_unique<Bullet>(m_position + Vector3(0.0f, 0.1f, 0.0f), m_shotRotate, Vector3(0.0f, 0.0f, 0.15f),"EnemyBullet"));
				CreateBullet();
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

	for (vector<unique_ptr<Bullet>>::iterator itr = m_pBullets.begin(); itr != m_pBullets.end(); itr++)
	{
		(*itr)->Update();
	}


	Matrix rotate = Matrix::CreateRotationY(m_enemyAngle);
	Matrix scale = Matrix::CreateScale(BOSS_SIZE);
	m_matrix = scale * rotate * Matrix::CreateTranslation(Vector3(m_position.x, 1.0f, m_position.z));

	m_collider.center = m_position;

	if (m_life == 0)
		m_pEnemy = nullptr;

	OutRangeBullet();
	if (m_isValid)  Blink();

}


// 描画
void Enemy::Render(const Matrix& _view)
{
	// モデル描画
	if (m_blinkTime % 5 == 0)
		if (m_life != 0)
			m_pEnemy->Draw(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(), *GameContext::Get<CommonStates>(), m_matrix, _view, GameContext::Get<Projection>()->GetMatrix());

	// 弾描画
	for (vector<unique_ptr<Bullet>>::iterator itr = m_pBullets.begin(); itr != m_pBullets.end(); itr++)
	{
		(*itr)->Render(_view);
	}
}

// 後始末
void Enemy::Finalize()
{

}

// プレイヤーを追いかける
void Enemy::ChasePlayer(Vector3 _playerPos)
{
	// プレイヤーへの向きを計算
	Vector3 dir = _playerPos - m_position;
	dir.Normalize();

	// 敵の移動
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
	for (vector<unique_ptr<Bullet>>::iterator itr = m_pBullets.begin(); itr != m_pBullets.end(); itr++)
	{
		(*itr)->Initialize(m_pBulletGeometric.get());
	}
}

// 弾が衝突した時
void Enemy::BulletOnCollision(int _number)
{
	m_pBullets[_number]->SetIsValid(false);

	vector<unique_ptr<Bullet>>::iterator itr = m_pBullets.begin();
	while (itr != m_pBullets.end())
	{
		if (!(*itr)->GetIsValid())
			itr = m_pBullets.erase(itr);
		else
			++itr;
	}
}

// 範囲外に出たら
void Enemy::OutRangeBullet()
{
	vector<unique_ptr<Bullet>>::iterator itr = m_pBullets.begin();

	while (itr != m_pBullets.end())
	{
		if ((*itr)->GetLife() < 0.0f)
			itr = m_pBullets.erase(itr);
		else
			++itr;
	}
}