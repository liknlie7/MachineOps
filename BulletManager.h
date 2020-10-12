#pragma once
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
	//std::unique_ptr<DirectX::GeometricPrimitive> GetBulletType(int _type)
	//{
	//	//return m_pBulletType[_type];
	//}

public: // �֐�

	// ������
	void Initialize();

	// �e�̐���
	Bullet* Create(const DirectX::SimpleMath::Vector3& _pos, const DirectX::SimpleMath::Vector3& _vec, const float& _angle);

	// �㏈��
	void Finalize();


public: // �萔

	// �e�̐�
	static const int NUM_BULLET;

private:
	// �e�̌`��
	enum BulletType
	{
		SPHERE = 1,	// ��
		BOX,		// �{�b�N�X

		ALL,		// �S�Ă̌`��
	};

	// �ۂ��e���a
	static const float SPHERE_BULLET_RADIUS;

	// �l�p���e�T�C�Y
	static const DirectX::SimpleMath::Vector3 BOX_BULLET_SIZE;


private: // �ϐ�

	// �e�̌`��
	std::unique_ptr<DirectX::GeometricPrimitive> m_pBulletType[ALL];

	// �e�z��
	//std::vector<std::unique_ptr<Bullet>>	m_pBulletArray;
};

