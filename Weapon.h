#pragma once

#include <GeometricPrimitive.h>
#include <SimpleMath.h>
#include <Keyboard.h>
#include <Mouse.h>

#include "DeviceResources.h"
#include "Projection.h"
#include "GameContext.h"
#include "GameObject.h"
#include "Bullet.h"

class Weapon : public GameObject
{
public: // ��{

	// �R���X�g���N�^
	Weapon();
	// �f�X�g���N�^
	~Weapon() {}

public: // �A�N�Z�T

	// ���W�ݒ�
	void SetWeaponPos(const DirectX::SimpleMath::Vector3& _pos)
	{
		m_position = _pos;
	}

	// �e�̍��W�擾
	//std::vector<DirectX::SimpleMath::Vector3> GetBulletPos() const
	//{
	//	std::vector<DirectX::SimpleMath::Vector3> bulletsPos;
	//	for (auto& numBullet : m_pBullets)
	//	{
	//		bulletsPos.push_back(numBullet->GetPosition());
	//	}
	//	return bulletsPos;
	//}

	// �v���C���[�̍��W�ݒ�
	void SetPlayerPos(const DirectX::SimpleMath::Vector3& _playerPos)
	{
		m_playerPos = _playerPos;
	}

	// �p�x�̐ݒ�
	void SetAngle(const float& _angle)
	{
		m_angle = _angle;
	}

	void SetBulletHitFlag(const bool& _isHitFlag)
	{
		bulletHitFlag = _isHitFlag;
	}
	void SetBulletNumber(const int& _bulletNumber)
	{
		bulletNumber = _bulletNumber;
	}

public: // �֐�

	// ������
	void Initialize();
	// �X�V
	void Update() override;
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
	//std::vector<std::unique_ptr<Bullet>>		 m_pBullets;

	// �v���C���[�̈ʒu
	DirectX::SimpleMath::Vector3				 m_playerPos;

	// �p�x
	float										 m_angle;

	bool										 bulletHitFlag;
	int											 bulletNumber;

};