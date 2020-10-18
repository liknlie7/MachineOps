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

// ����
void BulletManager::CreateBullet(const DirectX::SimpleMath::Vector3& _pos, const float& _speed, float _angle, DirectX::GeometricPrimitive* _bulletGeometry,const std::string& _tag)
{
	for (int i = 0; i < NUM_BULLET; i++)
	{
		if (!m_pBullets[i]->GetIsUsed())
		{
			// �e�̔��ˈʒu�̐ݒ�
			m_pBullets[i]->SetPosition(_pos);

			// �e�̑��x�̐ݒ�
			m_pBullets[i]->SetSpeed(_speed);

			// �p�x�̐ݒ�
			m_pBullets[i]->SetAngle(_angle);

			// �`��̐ݒ�
			m_pBullets[i]->SetBulletGeometry(_bulletGeometry);

			// �^�O�̐ݒ�
			m_pBullets[i]->SetTag(_tag);

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