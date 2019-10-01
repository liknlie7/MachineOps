#include "pch.h"

#include "Weapon.h"
#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using namespace std;

Weapon::Weapon()
	:m_pos(Vector3(0.0f, 0.0f, 0.5f))
	, bulletHitFlag(false)
	, bulletNumber(0)
{

}

// èâä˙âª
void Weapon::Initialize()
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>().Get();

	// ïêäÌÇÃçÏê¨
	m_pWeapon = GeometricPrimitive::CreateBox(deviceResources->GetD3DDeviceContext(), Vector3(0.1f, 0.1f, 0.5f));
	// íeÇÃçÏê¨
	m_pBulletGeometric = GeometricPrimitive::CreateSphere(deviceResources->GetD3DDeviceContext(), 0.3f);
}

// çXêV
void Weapon::Update()
{
	m_matrix = Matrix::CreateTranslation(m_pos) * Matrix::CreateRotationY(m_angle) *
		Matrix::CreateTranslation(m_playerPos);

	for (vector<unique_ptr<Bullet>>::iterator itr = m_pBullets.begin(); itr != m_pBullets.end(); itr++)
	{
		(*itr)->Update();
	}

	int i = 0;
	for (vector<unique_ptr<Bullet>>::iterator itr = m_pBullets.begin(); itr != m_pBullets.end(); itr++)
	{
		if (i == bulletNumber)
		{
			m_pBullets[bulletNumber]->SetHitFlag(bulletHitFlag);
		}
		if ((*itr)->GetHitFlag())
		{
			m_pBullets.erase(itr);
			(*itr)->SetHitFlag(false);
		}
		i++;
	}
}

// ï`âÊ
void Weapon::Render(Matrix _view)
{
	for (vector<unique_ptr<Bullet>>::iterator itr = m_pBullets.begin(); itr != m_pBullets.end(); itr++)
	{
		(*itr)->Render(_view);
	}
}

// å„énññ
void Weapon::Finalize()
{
	m_pWeapon.reset();
}

void Weapon::CreateBullet()
{
	// íeÇÃçÏê¨
	m_pBullets.push_back(make_unique<Bullet>(m_playerPos + Vector3(0.0f, 0.9f, 0.0f), m_angle));

	for (vector<unique_ptr<Bullet>>::iterator itr = m_pBullets.begin(); itr != m_pBullets.end(); itr++)
	{
		(*itr)->Initialize(m_pBulletGeometric.get());
	}
}