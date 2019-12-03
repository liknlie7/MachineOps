#include "pch.h"
#include "Enemy.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using namespace std;

// コンストラクタ
Enemy::Enemy(int _type)
	: m_blinkTime(50)
	, m_hitFlag(false)
	, m_playerPos(0.0f, 0.0f, 0.0f)
	, m_life(3)
{
	m_type = _type;
}

// デストラクタ
Enemy::~Enemy()
{
}

void Enemy::Initialize(DirectX::SimpleMath::Vector3 _pos)
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>().Get();

	// エフェクトファクトリの作成 
	EffectFactory* factory = new EffectFactory(deviceResources->GetD3DDevice());

	// 弾の形状作成
	m_pBulletGeometric = GeometricPrimitive::CreateSphere(deviceResources->GetD3DDeviceContext(), 0.3f);

	// テクスチャの読み込みパス指定 
	factory->SetDirectory(L"Resources/Models");

	switch (m_type)
	{
		// ノーマルタイプ
	case Normal:
		// モデルデータ読み込み 
		m_pEnemy = Model::CreateFromCMO(
			deviceResources->GetD3DDevice(),
			L"Resources/Models/Enemy1.cmo",
			*factory
		);
		delete factory;

		m_pos = _pos;
		// 速さの初期化
		m_speed = 0.08f;

		m_life = 3;

		m_collider.radius = 2.0f;
		m_collider.center = m_pos;
		//m_decisionAreaPos = m_pos;


		break;

		// 盾持ち
	case Shield:

		// モデルデータ読み込み 
		m_pEnemy = Model::CreateFromCMO(
			deviceResources->GetD3DDevice(),
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
	}

}

// 更新
void Enemy::Update()
{
	switch (m_type)
	{
	case Normal:
		//ChasePlayer(m_playerPos);
		//CreateBullet();
		//for (vector<unique_ptr<Bullet>>::iterator itr = m_pBullets.begin(); itr != m_pBullets.end(); itr++)
		//{
		//	(*itr)->Update();
		//}

		// 速度代入
		m_pos += m_vel;

		break;
	case Shield:
		break;
	}

	Vector3 m_dir;
	m_dir = m_playerPos - m_pos;
	m_dir.Normalize();

	m_angle = atan2(m_dir.x, m_dir.z);
	Matrix rotate = Matrix::CreateRotationY(m_angle);
	Matrix scale = Matrix::CreateScale(1.5f);
	m_mat = scale * rotate * Matrix::CreateTranslation(Vector3(m_pos.x, 1.0f, m_pos.z));

	m_collider.center = m_pos;

	if (m_life == 0)
		m_pEnemy = nullptr;
}


// 描画
void Enemy::Render(const Matrix& _view)
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>().Get();
	CommonStates* state = GameContext<CommonStates>().Get();
	Projection* proj = GameContext<Projection>().Get();

	// モデル描画
	//if (m_blinkTime % 5 == 0)
	if (m_life != 0)
		m_pEnemy->Draw(deviceResources->GetD3DDeviceContext(), *state, m_mat, _view, proj->GetMatrix());

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
		m_hitFlag = false;
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
	m_pBullets.push_back(make_unique<Bullet>(m_pos + Vector3(0.0f, 0.1f, 0.0f), m_angle, Vector3(0.0f, 0.0f, 0.15f)));

	//for (vector<unique_ptr<Bullet>>::iterator itr = m_pBullets.begin(); itr != m_pBullets.end(); itr++)
	//{
	//	(*itr)->Initialize(m_pBulletGeometric.get());
	//}
}
