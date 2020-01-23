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
	m_position = Vector3(0.0f, 0.0f, 0.5f);
}

// ������
void Weapon::Initialize()
{
	// ����̍쐬
	m_pWeapon = GeometricPrimitive::CreateBox(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(), Vector3(0.1f, 0.1f, 0.5f));
	// �e�̍쐬
	//m_pBulletGeometric = GeometricPrimitive::CreateSphere(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(), 0.3f);
	m_pBulletGeometric = GeometricPrimitive::CreateBox(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(),Vector3(0.1f,0.1f,1.5f));
}

// �X�V
void Weapon::Update()
{
	m_matrix = Matrix::CreateTranslation(m_position) * Matrix::CreateRotationY(m_angle) *
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
	//		//(*itr)->SetIsValid(false);
	//	}
	//	i++;
	//}
}

// �`��
void Weapon::Render(const Matrix& _view)
{
	for (vector<unique_ptr<Bullet>>::iterator itr = m_pBullets.begin(); itr != m_pBullets.end(); itr++)
	{
		(*itr)->Render(_view);
	}
}

// ��n��
void Weapon::Finalize()
{
	m_pWeapon.reset();
}

void Weapon::CreateBullet()
{
	// �e�̍쐬
	m_pBullets.push_back(make_unique<Bullet>(m_playerPos + Vector3(0.0f, 0.9f, 0.0f), m_angle, Vector3(0.0f, 0.0f, 0.8f),"PlayerBullet"));

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