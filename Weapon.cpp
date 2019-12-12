#include "pch.h"

#include "Weapon.h"
#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using namespace std;

Weapon::Weapon()
	: bulletHitFlag(false)
	, bulletNumber(0)
{
	m_pos = Vector3(0.0f, 0.0f, 0.5f);
}

// èâä˙âª
void Weapon::Initialize()
{
	DX::DeviceResources* deviceResources = GameContext::Get<DX::DeviceResources>();

	// ïêäÌÇÃçÏê¨
	m_pWeapon = GeometricPrimitive::CreateBox(deviceResources->GetD3DDeviceContext(), Vector3(0.1f, 0.1f, 0.5f));
	// íeÇÃçÏê¨
	m_pBulletGeometric = GeometricPrimitive::CreateSphere(deviceResources->GetD3DDeviceContext(), 0.3f);
}

// çXêV
void Weapon::Update()
{
	m_mat = Matrix::CreateTranslation(m_pos) * Matrix::CreateRotationY(m_angle) *
		Matrix::CreateTranslation(m_playerPos);

	for (vector<unique_ptr<Bullet>>::iterator itr = m_pBullets.begin(); itr != m_pBullets.end(); itr++)
	{
		(*itr)->Update();
	}

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
	//		(*itr)->SetIsValid(false);
	//	}
	//	i++;
	//}
}

// ï`âÊ
void Weapon::Render(const Matrix& _view)
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
	m_pBullets.push_back(make_unique<Bullet>(m_playerPos + Vector3(0.0f, 0.9f, 0.0f), m_angle, Vector3(0.0f, 0.0f, 0.3f)));

	for (vector<unique_ptr<Bullet>>::iterator itr = m_pBullets.begin(); itr != m_pBullets.end(); itr++)
	{
		(*itr)->Initialize(m_pBulletGeometric.get());
	}
}

void Weapon::BulletOnCollision(int _number)
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