#include "pch.h"
#include "Enemy.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// コンストラクタ
Enemy::Enemy()
	: /*m_decisionAreaPos(5.0f, 1.0f, 0.0f)*/
	 m_blinkTime(50)
	, m_hitFlag(false)
{
}

// デストラクタ
Enemy::~Enemy()
{
}

// ノーマル型初期化
void Enemy::InitializeNormal(DirectX::SimpleMath::Vector3 _pos)
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>().Get();

	// 当たり判定用
	//m_pDecisionArea = GeometricPrimitive::CreateSphere(deviceResources->GetD3DDeviceContext(), 2.0f);

	// エフェクトファクトリの作成 
	EffectFactory* factory = new EffectFactory(deviceResources->GetD3DDevice());
	// テクスチャの読み込みパス指定 
	factory->SetDirectory(L"Resources/Models");
	// ファイルを指定してモデルデータ読み込み 
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

}

// 盾持ち初期化
void Enemy::InitializeShield(DirectX::SimpleMath::Vector3 _pos)
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>().Get();

	// 当たり判定用
	//m_pDecisionArea = GeometricPrimitive::CreateSphere(deviceResources->GetD3DDeviceContext(), 2.0f);

	// エフェクトファクトリの作成 
	EffectFactory* factory = new EffectFactory(deviceResources->GetD3DDevice());
	// テクスチャの読み込みパス指定 
	factory->SetDirectory(L"Resources/Models");
	// ファイルを指定してモデルデータ読み込み 
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


}

// 更新
void Enemy::Update()
{

}

void Enemy::UpdateNormal(Vector3 _playerPos)
{
	ChasePlayer(_playerPos);
	if (m_hitFlag)
	{
		Blink();
	}
	// 速度代入
	m_pos += m_vel;

	Vector3 m_dir;
	m_dir = _playerPos - m_pos;
	m_dir.Normalize();
	float angle = atan2(m_dir.x, m_dir.z);
	Matrix rotate = Matrix::CreateRotationY(angle);
	Matrix scale = Matrix::CreateScale(1.5f);
	m_mat = scale * rotate * Matrix::CreateTranslation(Vector3(m_pos.x, 1.0f, m_pos.z));
	m_collider.center = m_pos;

}

void Enemy::UpdateShield(Vector3 _playerPos)
{
	if (m_hitFlag)
	{
		Blink();
	}
	Vector3 m_dir;
	m_dir = _playerPos - m_pos;
	m_dir.Normalize();
	float angle = atan2(m_dir.x, m_dir.z);
	Matrix rotate = Matrix::CreateRotationY(angle);
	Matrix scale = Matrix::CreateScale(1.5f);
	m_mat = scale * rotate * Matrix::CreateTranslation(Vector3(m_pos.x, 1.0f, m_pos.z));

	m_collider.center = m_pos;

}

// 描画
void Enemy::Render(const Matrix& _view)
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>().Get();
	CommonStates* state = GameContext<CommonStates>().Get();
	Projection* proj = GameContext<Projection>().Get();

	// モデル描画
	if (m_life > 0)
		if (m_blinkTime % 5 == 0)
			m_pEnemy->Draw(deviceResources->GetD3DDeviceContext(), *state, m_mat, _view, proj->GetMatrix());

	// 判定用
	//m_pDecisionArea->Draw(m_mat, _view, proj->GetMatrix(), Colors::Red, nullptr, true);
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
