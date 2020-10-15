#pragma once

#include <SimpleMath.h>
#include <GeometricPrimitive.h>

#include "Bullet.h"

// �e�Ǘ��N���X
class BulletManager
{
public: // ��{

	// �R���X�g���N�^
	BulletManager();

	// �f�X�g���N�^
	~BulletManager();

public: // �A�N�Z�T

	// �e�̌`��̎擾
	DirectX::GeometricPrimitive* GetBulletGeometry(int _geometryType)
	{
		return m_pBulletGeometry[_geometryType].get();
	}

public: // �֐�

	// ������
	void Initialize();

	// �X�V
	void Update();

	// �`��
	void Render(const DirectX::SimpleMath::Matrix& _view);

	// �e�̐���
	//Bullet* Create(const DirectX::SimpleMath::Vector3& _pos, const DirectX::SimpleMath::Vector3& _vec, const float& _angle);

	// ����
	void Shot(const DirectX::SimpleMath::Vector3& _pos, const float& _speed, const DirectX::SimpleMath::Matrix& _rotate, DirectX::GeometricPrimitive* _bulletGeometry);

	// �㏈��
	void Finalize();

public: // �萔

	// �e�̌`��
	enum BulletType
	{
		SPHERE = 1,	// ��
		BOX,		// �{�b�N�X

		ALL,		// �S�Ă̌`��
	};

private:
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
};

