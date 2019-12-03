#include "pch.h"

#include "BulletFactory.h"
#include "Bullet.h"

using namespace std;

using namespace DirectX;
using namespace DirectX::SimpleMath;

// �R���X�g���N�^
BulletFactory::BulletFactory()
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>().Get();

	m_pBulletGeometric = GeometricPrimitive::CreateSphere(deviceResources->GetD3DDeviceContext(), 0.3f);
}

// ������
void BulletFactory::Initialize()
{
	// �z��̃T�C�Y��ݒ肷��
	m_pBulletArray.resize(BULLET_NUM);

	// Bullet�I�u�W�F�N�g�𐶐����z��Ɋi�[����
	for (int i = 0; i < BULLET_NUM; i++)
	{
		// Bullet�I�u�W�F�N�g�𐶐�����
		m_pBulletArray[i] = make_unique<Bullet>();
		// �e���g�p�\�ɂ���
		m_pBulletArray[i]->IsUsed(false);
		// ����������
		m_pBulletArray[i]->Initialize(this);
	}
}

// �e�𐶐����� 
Bullet* BulletFactory::Create(const Vector3& position, const float& angle)
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		// �e���g�p���Ă��Ȃ������
		if (m_pBulletArray[i]->IsUsed() == false)
		{
			// �e�́u��s���v��ݒ肷��
			m_pBulletArray[i]->IsUsed(true);
			// �e�ɔ�s�p�x��ݒ肷��
			m_pBulletArray[i]->SetAngle(angle);
			// ��s�J�n�ʒu��ݒ肷��
			m_pBulletArray[i]->SetPosition(position);
			// Bullet�I�u�W�F�N�g��Ԃ�
			return m_pBulletArray[i].get();
		}
	}
	return nullptr;
}

// ��n��������
void BulletFactory::Finalize()
{
	// Bullet�I�u�W�F�N�g��j������
	for (int i = 0; i < BULLET_NUM; i++)
	{
		// Bullet�I�u�W�F�N�g��j������ 
		if (m_pBulletArray[i] != nullptr)
			m_pBulletArray[i].reset();
	}
	// Bullet�z���j������
	m_pBulletArray.clear();
}