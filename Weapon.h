#pragma once

#include <GeometricPrimitive.h>
#include <SimpleMath.h>
#include <Keyboard.h>
#include <Mouse.h>

#include "DeviceResources.h"
#include "StepTimer.h"
#include "Projection.h"
#include "GameContext.h"
#include "GameObject.h"
#include "Bullet.h"

class Bullet;

class Weapon : public GameObject
{
public: // ��{

	// �R���X�g���N�^
	Weapon();
	// �f�X�g���N�^
	~Weapon() {}

public: // �A�N�Z�T

	// ���W�ݒ�
	void SetWeaponPos(DirectX::SimpleMath::Vector3 _pos)
	{
		m_pos = _pos;
	}

	// �e�̍��W�擾
	std::vector<DirectX::SimpleMath::Vector3> GetBulletPos()
	{
		std::vector<DirectX::SimpleMath::Vector3> bulletsPos;
		for (auto& numBullet : m_pBullets)
		{
			bulletsPos.push_back(numBullet->GetPos());
		}
		return bulletsPos;
	}

	// �v���C���[�̍��W�ݒ�
	void SetPlayerPos(DirectX::SimpleMath::Vector3 _playerPos)
	{
		m_playerPos = _playerPos;
	}

	// �p�x�̐ݒ�
	void SetAngle(float _angle)
	{
		m_angle = _angle;
	}

	void SetBulletHitFlag(bool _bulletHitFlag)
	{
		bulletHitFlag = _bulletHitFlag;
	}
	void SetBulletNumber(int _bulletNumber)
	{
		bulletNumber = _bulletNumber;
	}

public: // �֐�

	// ������
	void Initialize();
	// �X�V
	void Update(DX::StepTimer const& timer) override;
	// �`��
	void Render(const DirectX::SimpleMath::Matrix& _view) override;
	// ��n��
	void Finalize();
	
	// �e�̐���
	void CreateBullet();

	void BulletOnCollision(int _number);

private: // �ϐ�

	// ����
	std::unique_ptr<DirectX::GeometricPrimitive> m_pWeapon;
	// �e
	std::unique_ptr<DirectX::GeometricPrimitive> m_pBulletGeometric;
	std::vector<std::unique_ptr<Bullet>>		 m_pBullets;

	// �v���C���[�̈ʒu
	DirectX::SimpleMath::Vector3				 m_playerPos;

	// �p�x
	float										 m_angle;

	bool										 bulletHitFlag;
	int											 bulletNumber;

};