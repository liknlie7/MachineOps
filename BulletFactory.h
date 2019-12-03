#pragma once

#include <vector>
#include <SimpleMath.h>
#include <GeometricPrimitive.h>

#include "DeviceResources.h"
#include "GameContext.h"

class Bullet;

class BulletFactory
{
public: // ��{

	// �R���X�g���N�^
	BulletFactory();
	~BulletFactory() {};

public: // �A�N�Z�b�T

	// �e�̌`����擾����
	DirectX::GeometricPrimitive* GetGeometric()
	{
		return m_pBulletGeometric.get();
	}

public: // �֐�

	// ������
	void Initialize();
	// �e�𔭎˂���
	Bullet* Create(const DirectX::SimpleMath::Vector3& position, const float& angle);
	// ��n��
	void Finalize();

public: // �萔

	static const int BULLET_NUM = 30;

private: // �ϐ�

	// �e�̌`��
	std::unique_ptr<DirectX::GeometricPrimitive> m_pBulletGeometric;
	
	// �e�z��
	std::vector<std::unique_ptr<Bullet>> m_pBulletArray;

};

