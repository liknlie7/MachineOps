#include "pch.h"

#include "Weapon.h"
#include "Player.h"

Weapon::Weapon()
	: bulletHitFlag(false)
	, bulletNumber(0)
{
	m_position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.5f);
}

// 初期化
void Weapon::Initialize()
{
	// 武器の作成
	m_pWeapon = DirectX::GeometricPrimitive::CreateBox(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(), DirectX::SimpleMath::Vector3(0.1f, 0.1f, 0.5f));
	// 弾の作成
	m_pBulletGeometric = DirectX::GeometricPrimitive::CreateBox(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(), DirectX::SimpleMath::Vector3(0.1f,0.1f,1.5f));
}

// 更新
void Weapon::Update()
{
	m_matrix = DirectX::SimpleMath::Matrix::CreateTranslation(m_position) * DirectX::SimpleMath::Matrix::CreateRotationY(m_angle) *
		DirectX::SimpleMath::Matrix::CreateTranslation(m_playerPos);

	//for (std::vector<std::unique_ptr<Bullet>>::iterator itr = m_pBullets.begin(); itr != m_pBullets.end(); itr++)
	//{
	//	(*itr)->Update();
	//}

	//int i = 0;
	//for (vector<unique_ptr<Bullet>>::iterator itr = m_pBullets.begin(); itr != m_pBullets.end(); itr++)
	//{
	//	if (i == bulletNumber)
	//	{
	//		m_pBullets[bulletNumber]->SetIsValid(bulletHitFlag);
	//	}
	//	if ((*itr)->GetIsValid())
	//	{
	//		m_pBullets.erase(itr);
	//		//(*itr)->SetIsValid(false);
	//	}
	//	i++;
	//}
}

// 描画
void Weapon::Render(const DirectX::SimpleMath::Matrix& _view)
{
	//for (std::vector<std::unique_ptr<Bullet>>::iterator itr = m_pBullets.begin(); itr != m_pBullets.end(); itr++)
	//{
	//	(*itr)->Render(_view);
	//}
}

// 後始末
void Weapon::Finalize()
{
	m_pWeapon.reset();
}

//void Weapon::CreateBullet()
//{
//	// 弾の作成
//	m_pBullets.push_back(std::make_unique<Bullet>(m_playerPos + DirectX::SimpleMath::Vector3(0.0f, 0.9f, 0.0f), DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.8f), m_angle));
//
//	for (std::vector<std::unique_ptr<Bullet>>::iterator itr = m_pBullets.begin(); itr != m_pBullets.end(); itr++)
//	{
//		(*itr)->Initialize(m_pBulletGeometric.get());
//	}
//}

//void Weapon::BulletOnCollision(int _number)
//{
//	m_pBullets[_number]->SetIsValid(false);
//
//	std::vector<std::unique_ptr<Bullet>>::iterator itr = m_pBullets.begin();
//
//	while (itr != m_pBullets.end())
//	{
//		if (!(*itr)->GetIsValid())
//			itr = m_pBullets.erase(itr);
//		else
//			++itr;
//	}
//}