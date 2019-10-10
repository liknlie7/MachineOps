#pragma once

#include <SimpleMath.h>
#include <GeometricPrimitive.h>
#include <Model.h>
#include <Effects.h>
#include <CommonStates.h>

#include "DeviceResources.h"
#include "Projection.h"
#include "Collision.h"
#include "GameObject.h"
#include "GameContext.h"
#include "Bullet.h"

// �G
class Enemy : public GameObject
{
public: // ��{

	// �R���X�g���N�^
	Enemy(int _type);
	// �f�X�g���N�^
	~Enemy();

public:

	enum Type
	{
		Normal = 1,
		Shield,
	};

public: // �A�N�Z�T

	// ���W�擾
	DirectX::SimpleMath::Vector3 Enemy::GetPos()
	{
		return m_pos;
	}

	// �ڐG����t���O�̎擾
	bool GetHitFlag()
	{
		return m_hitFlag;
	}

	// �ڐG����t���O�̐ݒ�
	void SetHitFlag(bool _hitFlag)
	{
		m_hitFlag = _hitFlag;
	}

	Collision::Sphere GetCollider()
	{
		return m_collider;
	}

	void SetPlayerPos(DirectX::SimpleMath::Vector3 _playerPos)
	{
		m_playerPos = _playerPos;
	}

public: // �֐�

	// ������
	void Initialize(DirectX::SimpleMath::Vector3 _pos);
	// �X�V
	void Update() override;
	// �`��
	void Render(const DirectX::SimpleMath::Matrix& _view) override;
	// ��n��
	void Finalize();

	// �v���C���[��ǂ�������
	void ChasePlayer(DirectX::SimpleMath::Vector3 _playerPos);
	// �_��
	void Blink();
	// �e�̍쐬
	void CreateBullet();

	// �Փ˂�����
	void OnCollision();


private: // �ϐ�

	// ���f��
	std::unique_ptr<DirectX::Model>	m_pEnemy;
	Collision::Sphere m_collider;

	// �e
	std::unique_ptr<DirectX::GeometricPrimitive> m_pBulletGeometric;
	std::vector<std::unique_ptr<Bullet>>		 m_pBullets;

	// �v���C���[�̈ʒu
	DirectX::SimpleMath::Vector3 m_playerPos;

	// �^�C�v
	int												m_type;
	// ����
	float											m_speed;
	// �p�x
	float											m_angle;
	// �̗�
	int												m_life;
	// �q�b�g�t���O
	bool											m_hitFlag;
	// �_�Ŏ���
	int												m_blinkTime;
};