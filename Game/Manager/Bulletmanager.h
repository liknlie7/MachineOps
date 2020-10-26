#pragma once

#include <SimpleMath.h>
#include <GeometricPrimitive.h>

#include "../Objects/Bullet.h"
#include "Collision.h"

// �e�Ǘ��N���X
class BulletManager
{
public: // ��{

	// �R���X�g���N�^
	BulletManager();

	// �f�X�g���N�^
	~BulletManager() {};

public: // �֐�

	// ������
	void Initialize();

	// �X�V
	void Update();

	// �`��
	void Render(const DirectX::SimpleMath::Matrix& _view);

	// ����
	void CreateBullet(const DirectX::SimpleMath::Vector3& _pos, const float& _speed, float _angle, DirectX::GeometricPrimitive* _bulletGeometry, const std::string& _tag);

	// �㏈��
	void Finalize();

public: // �A�N�Z�T

	// �e�̌`��̎擾
	DirectX::GeometricPrimitive* GetBulletGeometry(int _geometryType)
	{
		return m_pBulletGeometry[_geometryType].get();
	}

	// �e�̏��̎擾
	Bullet* GetBulletInfo(int _number)
	{
		return m_pBullets[_number].get();
	}

public: // �萔

	// �e�̌`��
	enum BulletType
	{
		SPHERE = 1,	// ��
		BOX,		// �{�b�N�X

		ALL,		// �S�Ă̌`��
	};

public:

	// �e�̐�
	static const int NUM_BULLET;

	// �ۂ��e���a
	static const float SPHERE_BULLET_RADIUS;

	// �l�p���e�T�C�Y
	static const DirectX::SimpleMath::Vector3 BOX_BULLET_SIZE;


private: // �ϐ�

	// �e�̌`��
	std::unique_ptr<DirectX::GeometricPrimitive> m_pBulletGeometry[BulletType::ALL];

	// �e�z��
	std::vector<std::unique_ptr<Bullet>>		 m_pBullets;

	// sphere�p����
	Collision::Sphere	m_sphereCollider;

	// box�p����
	Collision::Box		m_boxCollider;
};

