#pragma once

#include <SimpleMath.h>
#include <GeometricPrimitive.h>
#include <Model.h>
#include <Effects.h>
#include <CommonStates.h>
#include <SpriteBatch.h>

#include "DeviceResources.h"
#include "Projection.h"
#include "Collision.h"
#include "GameObject.h"
#include "GameContext.h"
//#include "Bullet.h"
#include "GameObject.h"
#include "ResourceManager.h"
//#include "BulletManager.h"

// �G
class Enemy : public GameObject
{
public: // ��{

	// �R���X�g���N�^
	Enemy(const int _type);
	// �f�X�g���N�^
	~Enemy() {};

public:

	// �G�̎��
	enum EnemyType
	{
		NORMAL_ENEMY = 1,
		SHIELD_ENEMY,
		BOSS_ENEMY,
	};

	// �ˌ��̎��
	enum ShotType
	{
		NORMAL_SHOT,			// �ʏ�
		ALL_DIRECTION_SHOT,		// �S����
		WINDER_SHOT,			// ���C���_�[
		WHORL_SHOT,				// �����܂�
	};

public: // �A�N�Z�T

	// ���f���̏��̎擾
	//DirectX::Model* GetModel() const
	//{
	//	return m_pEnemy.get();
	//}

	// ���W�擾
	DirectX::SimpleMath::Vector3 GetPos() const
	{
		return m_position;
	}

	// �e�̍��W�擾
	//std::vector<DirectX::SimpleMath::Vector3> GetBulletPos() const
	//{
	//	std::vector<DirectX::SimpleMath::Vector3> bulletsPos;
	//	for (auto& numBullet : m_pBullets)
	//	{
	//		bulletsPos.push_back(numBullet->GetPos());
	//	}
	//	return bulletsPos;
	//}

	// �ڐG����t���O�̎擾
	bool GetIsValid() const
	{
		return m_isValid;
	}

	// �ڐG����t���O�̐ݒ�
	void SetIsValid(const bool& _hitFlag)
	{
		m_isValid = _hitFlag;
	}

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
	//void SetBulletManager(BulletManager* _bullet)
	//{
	//	m_pBulletManager = _bullet;
	//}


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
	//// �e���Փ˂�����
	//void BulletOnCollision(int _number);
	//// �e����ʊO�ɏo����
	//void OutRangeBullet();


private: // �萔

	// �T�C�Y
	static const float SIZE;
	// �{�X�T�C�Y
	static const float BOSS_SIZE;

private: // �ϐ�

	// ���f��
	std::weak_ptr<DirectX::Model>					m_pEnemy;
	Collision::Sphere								m_collider;

	// �e
	//std::unique_ptr<DirectX::GeometricPrimitive>	m_pBulletGeometric;
	//std::vector<std::unique_ptr<Bullet>>			m_pBullets;

	//// �e�Ǘ��p�I�u�W�F�N�g
	//BulletManager*									m_pBulletManager;

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
	float											m_maxLife;
	float											m_life;
	// �q�b�g�t���O
	bool											m_isValid;
	// �_�Ŏ���
	int												m_blinkTime;


};