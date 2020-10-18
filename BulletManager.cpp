#include "pch.h"
#include "BulletManager.h"

// 弾の数
const int BulletManager::NUM_BULLET = 300;

// 丸い弾半径
const float BulletManager::SPHERE_BULLET_RADIUS = 0.3f;

// 四角い弾サイズ
const DirectX::SimpleMath::Vector3 BulletManager::BOX_BULLET_SIZE = DirectX::SimpleMath::Vector3(0.1f, 0.1f, 1.5f);

// コンストラクタ
BulletManager::BulletManager()
{
	// 弾の形状を作成する
	m_pBulletGeometry[SPHERE] = DirectX::GeometricPrimitive::CreateSphere(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(), SPHERE_BULLET_RADIUS);
	m_pBulletGeometry[BOX] = DirectX::GeometricPrimitive::CreateBox(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(), BOX_BULLET_SIZE);
}

// デストラクタ
BulletManager::~BulletManager()
{

}

// 初期化
void BulletManager::Initialize()
{
	// 配列のサイズを設定
	m_pBullets.resize(NUM_BULLET);

	for (int i = 0; i < NUM_BULLET; i++)
	{
		// Bulletオブジェクト生成
		m_pBullets[i] = std::make_unique<Bullet>();
	}
}

// 更新
void BulletManager::Update()
{
	for (int i = 0; i < NUM_BULLET; i++)
	{
		if (m_pBullets[i]->GetIsUsed())
		{
			m_pBullets[i]->Update();
		}
	}
}

// 描画
void BulletManager::Render(const DirectX::SimpleMath::Matrix& _view)
{
	for (int i = 0; i < NUM_BULLET; i++)
	{
		if (m_pBullets[i]->GetIsUsed())
		{
			m_pBullets[i]->Render(_view);
		}
	}
}

// 発射
void BulletManager::CreateBullet(const DirectX::SimpleMath::Vector3& _pos, const float& _speed, float _angle, DirectX::GeometricPrimitive* _bulletGeometry,const std::string& _tag)
{
	for (int i = 0; i < NUM_BULLET; i++)
	{
		if (!m_pBullets[i]->GetIsUsed())
		{
			// 弾の発射位置の設定
			m_pBullets[i]->SetPosition(_pos);

			// 弾の速度の設定
			m_pBullets[i]->SetSpeed(_speed);

			// 角度の設定
			m_pBullets[i]->SetAngle(_angle);

			// 形状の設定
			m_pBullets[i]->SetBulletGeometry(_bulletGeometry);

			// タグの設定
			m_pBullets[i]->SetTag(_tag);

			// 使用中に変更
			m_pBullets[i]->SetIsUsed(true);

			break;
		}
	}
}

// 後処理
void BulletManager::Finalize()
{
	for (int i = 0; i < NUM_BULLET; i++)
	{
		// Bulletオブジェクトを破棄する
		if (m_pBullets[i] != nullptr)
		{
			m_pBullets[i].reset();
		}

		// Bullet配列を破棄する
		m_pBullets.clear();
	}
}