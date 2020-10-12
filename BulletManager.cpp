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
	m_pBulletType[SPHERE] = DirectX::GeometricPrimitive::CreateSphere(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(), SPHERE_BULLET_RADIUS);
	m_pBulletType[BOX] = DirectX::GeometricPrimitive::CreateBox(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(), BOX_BULLET_SIZE);
}

// デストラクタ
BulletManager::~BulletManager()
{

}

// 初期化
//void BulletManager::Initialize()
//{
//	// 配列のサイズを設定
//	m_pBulletArray.resize(NUM_BULLET);
//
//	for (int i = 0; i < NUM_BULLET; i++)
//	{
//		// Bulletオブジェクト生成
//		m_pBulletArray[i] = std::make_unique<Bullet>();
//		
//		// 弾を使用可能にする
//		m_pBulletArray[i]->SetIsUsed(false);
//	}
//}

// 弾の生成
//Bullet* BulletManager::Create(const DirectX::SimpleMath::Vector3 & _pos, const DirectX::SimpleMath::Vector3 & _vec, const float & _angle)
//{
//	for (int i = 0; i < NUM_BULLET; i++)
//	{
//		if (m_pBulletArray[i]->GetIsUsed() == false)
//		{
//			// 弾を使用中に変更
//			m_pBulletArray[i]->SetIsUsed(true);
//
//			// 角度の設定
//			m_pBulletArray[i]->SetAngle(_angle);
//
//			// 弾の発射位置を設定
//			m_pBulletArray[i]->SetPosition(_pos);
//
//			// Bulletオブジェクトを返す
//			return m_pBulletArray[i].get();
//		}
//	}
//	return nullptr;
//}

// 後処理
//void BulletManager::Finalize()
//{
//	for (int i = 0; i < NUM_BULLET; i++)
//	{
//		// Bulletオブジェクトを破棄する
//		if (m_pBulletArray[i] != nullptr)
//		{
//			m_pBulletArray[i].reset();
//		}
//
//		// Bullet配列を破棄する
//		m_pBulletArray.clear();
//	}
//}