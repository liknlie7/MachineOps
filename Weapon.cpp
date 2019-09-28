#include "pch.h"

#include "Weapon.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using namespace std;

Weapon::Weapon()
	:m_pos(Vector3(0.0f, 0.0f, 0.5f))
	, bulletHitFlag(false)
	, bulletNumber(0)
{

}

// 初期化
void Weapon::Initialize()
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>().Get();

	// 武器の作成
	m_pWeapon = GeometricPrimitive::CreateBox(deviceResources->GetD3DDeviceContext(), Vector3(0.1f, 0.1f, 0.5f));
	// 弾の作成
	m_pBulletGeometric = GeometricPrimitive::CreateSphere(deviceResources->GetD3DDeviceContext(), 0.3f);
}

// 更新
void Weapon::Update(DirectX::SimpleMath::Vector3 _playerPos, float _angle)
{
	m_matrix = Matrix::CreateTranslation(m_pos) * Matrix::CreateRotationY(_angle) *
		Matrix::CreateTranslation(_playerPos);
	m_playerPos = _playerPos;

	for (vector<unique_ptr<Bullet>>::iterator itr = m_pBullets.begin(); itr != m_pBullets.end(); itr++)
	{
		(*itr)->Update(_angle);
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

// 描画
void Weapon::Render(Matrix _view, Vector4 _color)
{
	//m_pWeapon->Draw(m_matrix, _view, _proj, _color);

	for (vector<unique_ptr<Bullet>>::iterator itr = m_pBullets.begin(); itr != m_pBullets.end(); itr++)
	{
		(*itr)->Render(_view);
	}

}

// 後始末
void Weapon::Finalize()
{
	m_pWeapon.reset();
}

void Weapon::CreateBullet(float _angle)
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>().Get();

	// 弾の作成
	m_pBullets.push_back(make_unique<Bullet>(m_playerPos + Vector3(0.0f, 0.9f, 0.0f), _angle));

	for (vector<unique_ptr<Bullet>>::iterator itr = m_pBullets.begin(); itr != m_pBullets.end(); itr++)
	{
		(*itr)->Initialize(m_pBulletGeometric.get());
	}

}