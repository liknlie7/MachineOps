#include "pch.h"

#include "BulletFactory.h"
#include "Bullet.h"

using namespace std;

using namespace DirectX;
using namespace DirectX::SimpleMath;

// コンストラクタ
BulletFactory::BulletFactory()
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>().Get();

	m_pBulletGeometric = GeometricPrimitive::CreateSphere(deviceResources->GetD3DDeviceContext(), 0.3f);
}

// 初期化
void BulletFactory::Initialize()
{
	// 配列のサイズを設定する
	m_pBulletArray.resize(BULLET_NUM);

	// Bulletオブジェクトを生成し配列に格納する
	for (int i = 0; i < BULLET_NUM; i++)
	{
		// Bulletオブジェクトを生成する
		m_pBulletArray[i] = make_unique<Bullet>();
		// 弾を使用可能にする
		m_pBulletArray[i]->IsUsed(false);
		// 初期化する
		m_pBulletArray[i]->Initialize(this);
	}
}

// 弾を生成する 
Bullet* BulletFactory::Create(const Vector3& position, const float& angle)
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		// 弾を使用していないければ
		if (m_pBulletArray[i]->IsUsed() == false)
		{
			// 弾は「飛行中」を設定する
			m_pBulletArray[i]->IsUsed(true);
			// 弾に飛行角度を設定する
			m_pBulletArray[i]->SetAngle(angle);
			// 飛行開始位置を設定する
			m_pBulletArray[i]->SetPosition(position);
			// Bulletオブジェクトを返す
			return m_pBulletArray[i].get();
		}
	}
	return nullptr;
}

// 後始末をする
void BulletFactory::Finalize()
{
	// Bulletオブジェクトを破棄する
	for (int i = 0; i < BULLET_NUM; i++)
	{
		// Bulletオブジェクトを破棄する 
		if (m_pBulletArray[i] != nullptr)
			m_pBulletArray[i].reset();
	}
	// Bullet配列を破棄する
	m_pBulletArray.clear();
}