#pragma once

#include <SimpleMath.h>
#include <Model.h>

#include "GameObject.h"
#include "BulletManager.h"
#include "GameObject.h"
#include "EnemyData.h"
#include "Collision.h"

// �G�l�~�[
class Enemy : public GameObject
{
public: // ��{

	// �R���X�g���N�^
	Enemy(const EnemyData& _enemyData);

	// �f�X�g���N�^
	~Enemy() {};

public: // �֐�

	// ������
	void Initialize(const DirectX::SimpleMath::Vector3& _pos);
	
	// �X�V
	void Update() override;
	
	// �`��
	void Render(const DirectX::SimpleMath::Matrix& _view) override;
	
	// ��n��
	void Finalize() {};

	// �Փ˂�����
	void OnCollision();

private: // �֐�

	// �v���C���[��ǂ�������
	void ChasePlayer(const DirectX::SimpleMath::Vector3& _playerPos);

	// �_��
	void Blink();

	// �ˌ��p�^�[���̐؂�ւ�
	void ChangeShotPattern();

	// �v���C���[�̕����Ɍ�����
	void TurnToDirectionPlayer();

	// �e������
	void Shot();

public: // �A�N�Z�T

	// �R���C�_�[�̎擾
	Collision::Sphere GetCollider() const
	{
		return m_collider;
	}

	// �v���C���[�̈ʒu�̐ݒ�
	void SetPlayerPos(const DirectX::SimpleMath::Vector3& _playerPos)
	{
		m_playerPos = _playerPos;
	}

	// �̗͂̍ő�l�擾
	float GetMaxLife() const
	{
		return m_maxLife;
	}
	// �̗͂̎擾
	float GetLife() const
	{
		return m_life;
	}

	// �e�Ǘ��N���X�̃A�h���X��ݒ�
	void SetBulletManager(BulletManager* _bullet)
	{
		m_pBulletManager = _bullet;
	}

public: // �萔

	// �G�l�~�[�̎��
	enum EnemyType
	{
		NORMAL_ENEMY = 1,	// �ʏ�
		SHIELD_ENEMY,		// ��
		BOSS_ENEMY,			// �{�X
	};

private: // �萔

	// �ˌ��̎��
	enum ShotType
	{
		NORMAL_SHOT = 1,		// �ʏ�
		ALL_DIRECTION_SHOT,		// �S����
		WHORL_SHOT,				// �����܂�
	};

	// �T�C�Y
	static const float SIZE;

	// �{�X�T�C�Y
	static const float BOSS_SIZE;

	// �e�����Ԋu
	static const float NORMAL_SHOT_INTERVEL;
	static const float ALL_DIRECTION_SHOT_INTERVEL;
	static const float WHORL_SHOT_INTERVEL;

	// �_�ŊԊu
	static const float BLINK_TIME;

	// �e�̑��x
	static const float BULLET_SPEED;

private: // �ϐ�

	// ���f��
	std::weak_ptr<DirectX::Model>					m_pEnemy;
	Collision::Sphere								m_collider;

	// �e�Ǘ��p�I�u�W�F�N�g
	BulletManager*									m_pBulletManager;

	// �v���C���[�̈ʒu
	DirectX::SimpleMath::Vector3					m_playerPos;

	// �^�C�v
	int												m_enemyType;
	
	// �ˌ��^�C�v
	int												m_shotType;
	
	// �ˌ��C���^�[�o��
	float											m_shotInterval;
	
	// �e�̉�]
	float											m_shotRotate;
	
	// ����
	float											m_moveSpeed;
	
	// �G�l�~�[�@�̊p�x
	float											m_enemyAngle;
	
	// Way��
	int												m_shotWayNum;
	
	// �e�̒[�̊p�x
	float											m_bulletEndAngle;
	
	// �e�̊p�x�̊Ԋu
	float											m_bulletChangeAngle;
	
	// �̗�
	float											m_life;
	float											m_maxLife;
		
	// �q�b�g�t���O
	bool											m_hitFlag;

	// �_�Ŏ���
	int												m_blinkTime;
};