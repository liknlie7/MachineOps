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

	DirectX::Model* GetModel()
	{
		return m_pEnemy.get();
	}

	// ���W�擾
	DirectX::SimpleMath::Vector3 GetPos()
	{
		return m_pos;
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

	// �ڐG����t���O�̎擾
	bool GetIsValid()
	{
		return m_isValid;
	}

	// �ڐG����t���O�̐ݒ�
	void SetIsValid(bool _hitFlag)
	{
		m_isValid = _hitFlag;
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
	void Update(DX::StepTimer const& timer) override;
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
	// �e���Փ˂�����
	void BulletOnCollision(int _number);
	// �e����ʊO�ɏo����
	void OutRangeBullet();


private: // �ϐ�

	// ���f��
	std::unique_ptr<DirectX::Model>					m_pEnemy;
	Collision::Sphere								m_collider;

	// �e
	std::unique_ptr<DirectX::GeometricPrimitive>	m_pBulletGeometric;
	std::vector<std::unique_ptr<Bullet>>			m_pBullets;

	// �v���C���[�̈ʒu
	DirectX::SimpleMath::Vector3					m_playerPos;

	// �^�C�v
	int												m_type;
	// ����
	float											m_speed;
	// �G�@�̊p�x
	float											m_enemyAngle;
	// Way��
	int												m_wayNum;
	// �e�̒[�̊p�x
	float											m_bulletEndAngle;
	// �e�̊p�x�̊Ԋu
	float											m_changeAngle;
	// �̗�
	int												m_life;
	// �q�b�g�t���O
	bool											m_isValid;
	// �_�Ŏ���
	int												m_blinkTime;


};