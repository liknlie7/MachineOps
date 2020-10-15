#include "pch.h"
#include "BulletManager.h"

// �e�̐�
const int BulletManager::NUM_BULLET = 300;

// �ۂ��e���a
const float BulletManager::SPHERE_BULLET_RADIUS = 0.3f;

// �l�p���e�T�C�Y
const DirectX::SimpleMath::Vector3 BulletManager::BOX_BULLET_SIZE = DirectX::SimpleMath::Vector3(0.1f, 0.1f, 1.5f);

// �R���X�g���N�^
BulletManager::BulletManager()
{
	// �e�̌`����쐬����
	m_pBulletGeometry[SPHERE] = DirectX::GeometricPrimitive::CreateSphere(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(), SPHERE_BULLET_RADIUS);
	m_pBulletGeometry[BOX] = DirectX::GeometricPrimitive::CreateBox(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(), BOX_BULLET_SIZE);
}

// �f�X�g���N�^
BulletManager::~BulletManager()
{

}

// ������
void BulletManager::Initialize()
{
	// �z��̃T�C�Y��ݒ�
	m_pBullets.resize(NUM_BULLET);

	for (int i = 0; i < NUM_BULLET; i++)
	{
		// Bullet�I�u�W�F�N�g����
		m_pBullets[i] = std::make_unique<Bullet>();
	}
}

// �X�V
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

// �`��
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

// �e�̐���
//Bullet* BulletManager::Create(const DirectX::SimpleMath::Vector3 & _pos, const DirectX::SimpleMath::Vector3 & _vec, const float & _angle)
//{
//	for (int i = 0; i < NUM_BULLET; i++)
//	{
//		if (m_pBulletArray[i]->GetIsUsed() == false)
//		{
//			// �e���g�p���ɕύX
//			m_pBulletArray[i]->SetIsUsed(true);
//
//			// �p�x�̐ݒ�
//			m_pBulletArray[i]->SetAngle(_angle);
//
//			// �e�̔��ˈʒu��ݒ�
//			m_pBulletArray[i]->SetPosition(_pos);
//
//			// Bullet�I�u�W�F�N�g��Ԃ�
//			return m_pBulletArray[i].get();
//		}
//	}
//	return nullptr;
//}

// ����
void BulletManager::Shot(const DirectX::SimpleMath::Vector3& _pos, const DirectX::SimpleMath::Vector3& _vel, const DirectX::SimpleMath::Matrix& _rotate, DirectX::GeometricPrimitive* _bulletGeometry)
{
	for (int i = 0; i < NUM_BULLET; i++)
	{
		if (!m_pBullets[i]->GetIsUsed())
		{
			// �e�̔��ˈʒu�̐ݒ�
			m_pBullets[i]->SetPosition(_pos);

			// �e�̑��x�̐ݒ�
			m_pBullets[i]->SetVelocity(_vel);

			// �p�x�̐ݒ�
			//m_pBullets[i]->SetAngle(_angle);
			m_pBullets[i]->SetRotation(_rotate);

			// �`��̐ݒ�
			m_pBullets[i]->SetBulletGeometry(_bulletGeometry);

			// �g�p���ɕύX
			m_pBullets[i]->SetIsUsed(true);

			break;
		}
	}
}

// �㏈��
void BulletManager::Finalize()
{
	for (int i = 0; i < NUM_BULLET; i++)
	{
		// Bullet�I�u�W�F�N�g��j������
		if (m_pBullets[i] != nullptr)
		{
			m_pBullets[i].reset();
		}

		// Bullet�z���j������
		m_pBullets.clear();
	}
}