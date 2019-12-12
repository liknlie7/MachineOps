#include "pch.h"
#include "Enemy.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using namespace std;

// コンストラクタ
Enemy::Enemy(int _type)
	: m_blinkTime(50)
	, m_isValid(false)
	, m_playerPos(0.0f, 0.0f, 0.0f)
	, m_life(300)
	, m_wayNum(3)
	, m_changeAngle(30)
	, m_bulletEndAngle(0)
	, m_shotInterval(10.0f)
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
		
	case NORMAL_TYPE: // ノーマルタイプ

		// モデルデータ読み込み 
		m_pEnemy = Model::CreateFromCMO(
			GameContext::Get<DX::DeviceResources>()->GetD3DDevice(),
			L"Resources/Models/Enemy1.cmo",
			*factory
		);
		delete factory;

		m_pos = _pos;
		// 速さの初期化
		m_speed = 0.08f;

		m_life = 300;

		m_collider.radius = 2.0f;
		m_collider.center = m_pos;
		//m_decisionAreaPos = m_pos;

		break;

		// 盾持ち
	case SHIELD_TYPE:

		// モデルデータ読み込み 
		m_pEnemy = Model::CreateFromCMO(
			GameContext::Get<DX::DeviceResources>()->GetD3DDevice(),
			L"Resources/Models/Enemy2.cmo",
			*factory
		);
		delete factory;

		m_pos = _pos;
		// 速さの初期化
		m_speed = 0.05f;

		m_life = 5;

		m_collider.radius = 2.0f;
		m_collider.center = m_pos;
		//m_decisionAreaPos = m_pos;

		break;

	case BOSS_TYPE:
		// モデルデータ読み込み 
		m_pEnemy = Model::CreateFromCMO(
			GameContext::Get<DX::DeviceResources>()->GetD3DDevice(),
			L"Resources/Models/Enemy1.cmo",
			*factory
		);
		delete factory;

		m_pos = _pos;
		// 速さの初期化
		m_speed = 0.08f;

		m_life = 30;
		m_shotType = ALL_DIRECTION_SHOT;
		m_collider.radius = 2.0f;
		m_collider.center = m_pos;
		//m_decisionAreaPos = m_pos;

		break;
	}

}

// 更新
void Enemy::Update()
{
	Vector3 m_dir;
	m_dir = m_playerPos - m_pos;
	m_dir.Normalize();

	switch (m_enemyType)
	{
	case NORMAL_TYPE:

		//ChasePlayer(m_playerPos);

		m_bulletEndAngle -= 180 + m_wayNum / 2 * m_changeAngle;

		//for (int i = 0; i < m_wayNum; i++)
		//{
		//	CreateBullet();
		//}

		break;
	case SHIELD_TYPE:

		break;
	case BOSS_TYPE:
		
		

		m_playerPos.Normalize();
		Vector3 baseDir = m_playerPos;


		break;
	}
	
	m_shotInterval++;

	switch (m_shotType)
	{
	case NORMAL_SHOT:
		break;
	case ALL_DIRECTION_SHOT:
		
		if (m_shotInterval > 15.0f)
		{
			for (int rad = 0; rad < 130; rad += 6)
			{
				m_pBullets.push_back(make_unique<Bullet>(m_pos + Vector3(0.0f, 0.1f, 0.0f), (float)rad, Vector3(0.0f, 0.0f, 0.15f)));
				CreateBullet();
				m_shotInterval = 0;
			}
		}
		break;
	}

	// 速度代入
	m_pos += m_vel;

	for (vector<unique_ptr<Bullet>>::iterator itr = m_pBullets.begin(); itr != m_pBullets.end(); itr++)
	{
		(*itr)->Update();
	}


	m_enemyAngle = atan2(m_dir.x, m_dir.z);
	Matrix rotate = Matrix::CreateRotationY(m_enemyAngle);
	Matrix scale = Matrix::CreateScale(1.5f);
	m_mat = scale * rotate * Matrix::CreateTranslation(Vector3(m_pos.x, 1.0f, m_pos.z));

	m_collider.center = m_pos;

	if (m_life == 0)
		m_pEnemy = nullptr;

	OutRangeBullet();


}


// 描画
void Enemy::Render(const Matrix& _view)
{
	// モデル描画
	//if (m_blinkTime % 5 == 0)
	if (m_life != 0)
		m_pEnemy->Draw(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(), *GameContext::Get<CommonStates>(), m_mat, _view, GameContext::Get<Projection>()->GetMatrix());

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
	Vector3 dir = _playerPos - m_pos;
	dir.Normalize();

	// 敵の移動
	m_pos += dir * m_speed;
}

// 点滅
void Enemy::Blink()
{
	m_blinkTime--;

	if (m_blinkTime < 0)
	{
		m_isValid = false;
		m_blinkTime = 50;
	}
}

// 衝突した時
void Enemy::OnCollision()
{
	m_life--;

	Blink();
}

// 弾の作成
void Enemy::CreateBullet()
{
	for (vector<unique_ptr<Bullet>>::iterator itr = m_pBullets.begin(); itr != m_pBullets.end(); itr++)
	{
		(*itr)->Initialize(m_pBulletGeometric.get());
	}
}

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

void Enemy::OutRangeBullet()
{
	vector<unique_ptr<Bullet>>::iterator itr = m_pBullets.begin();

	while (itr != m_pBullets.end())
	{
		if (!(*itr)->GetLife() < 0.0f)
			itr = m_pBullets.erase(itr);
		else
			++itr;
	}
}