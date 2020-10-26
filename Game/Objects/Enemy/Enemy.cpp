#include "../../pch.h"

#include "../../Common/DeviceResources.h"
#include "../../Common/Projection.h"
#include "../../Common/GameContext.h"
#include "../../Manager/ResourceManager.h"
#include "../Player/Player.h"
#include "Enemy.h"

// �ʏ�̑傫��
const float Enemy::SIZE = 1.5f;

// �{�X�̑傫��
const float Enemy::BOSS_SIZE = 8.0f;

// �e�����Ԋu
const float Enemy::NORMAL_SHOT_INTERVEL = 15.0f;
const float Enemy::ALL_DIRECTION_SHOT_INTERVEL = 50.0f;
const float Enemy::WHORL_SHOT_INTERVEL = 10.0f;

// �_�ŊԊu
const int Enemy::BLINK_TIME = 30;

// �e�̑��x
const float Enemy::BULLET_SPEED = 0.15f;

// �R���X�g���N�^
Enemy::Enemy(const EnemyData& _enemyData)
	: m_blinkTime(0)
	, m_hitFlag(false)
	, m_playerPos(DirectX::SimpleMath::Vector3::Zero)
	, m_shotInterval(0.0f)
	, m_shotRotate(0.0f)
{
	// �G�l�~�[��ސݒ�
	m_enemyType = _enemyData.enemyType;

	// ���C�t�ݒ�
	m_maxLife = m_life = (float)_enemyData.life;

	// �ړ����x�ݒ�
	m_moveSpeed = _enemyData.moveSpeed;

	// �����蔻�蔼�a�ݒ�
	m_collider.radius = _enemyData.collider;

	// �ˌ���ސݒ�
	m_shotType = _enemyData.shotType;
}

// ������
void Enemy::Initialize(const DirectX::SimpleMath::Vector3& _pos)
{
	switch (m_enemyType)
	{
	case NORMAL_ENEMY: // �m�[�}���^�C�v

		// �ʒu������
		m_position = _pos;

		// �����蔻�蒆�S�_�̐ݒ�
		m_collider.center = m_position;

		break;

	case SHIELD_ENEMY: // ������

		// �ʒu������
		m_position = _pos;

		// �����蔻�蒆�S�_�̐ݒ�
		m_collider.center = m_position;

		break;

	case BOSS_ENEMY: // �{�X

		// �G�l�~�[���f����shared_ptr���󂯎��
		m_pEnemy = std::weak_ptr<DirectX::Model>(ResourceManager::GetInstance()->GetModel(L"Resources/Models/Enemy1.cmo"));

		// �ʒu������
		m_position = _pos;

		// �����蔻�蒆�S�_�̐ݒ�
		m_collider.center = m_position;

		break;
	}
}

// �X�V
void Enemy::Update()
{
	// �v���C���[�̕����Ɍ�����
	TurnToDirectionPlayer();

	switch (m_enemyType)
	{
	case NORMAL_ENEMY: // �m�[�}���^�C�v

		// �v���C���[��ǂ�������
		ChasePlayer(m_playerPos);

		break;

	case SHIELD_ENEMY: // ������

		break;

	case BOSS_ENEMY: // �{�X

		// �v���C���[��ǂ�������
		ChasePlayer(m_playerPos);

		// �ˌ��p�^�[���̐؂�ւ�
		ChangeShotPattern();

		break;
	}

	// �e������
	Shot();

	// ���x���
	m_position += m_velocity;

	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateRotationY(m_enemyAngle);
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(BOSS_SIZE);
	m_matrix = scale * rotate * DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(m_position.x, 1.0f, m_position.z));

	// �����蔻��̒��S���ʒu�Őݒ�
	m_collider.center = m_position;

	// �q�b�g���Ă�����
	if (m_hitFlag)
	{
		// �_�ł�����
		Blink();
	}
}


// �`��
void Enemy::Render(const DirectX::SimpleMath::Matrix& _view)
{
	ID3D11DeviceContext1* context = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	DirectX::CommonStates* state = GameContext::Get<DirectX::CommonStates>();
	DirectX::SimpleMath::Matrix proj = GameContext::Get<Projection>()->GetMatrix();

	// ���f���`��
	if (m_blinkTime % 5 == 0)
	{
		if (m_life != 0)
		{
			if (std::shared_ptr<DirectX::Model> sptr = m_pEnemy.lock())
			{
				sptr->Draw(context, *state, m_matrix, _view, proj);
			}
		}
	}
}

// �v���C���[��ǂ�������
void Enemy::ChasePlayer(const DirectX::SimpleMath::Vector3& _playerPos)
{
	// �v���C���[�ւ̌������v�Z
	DirectX::SimpleMath::Vector3 dir = _playerPos - m_position;
	dir.Normalize();

	// �G�l�~�[�̈ړ�
	m_position += dir * m_moveSpeed;
}

// �_��
void Enemy::Blink()
{
	m_blinkTime--;

	if (m_blinkTime < 0)
	{
		m_hitFlag = false;
		m_blinkTime = BLINK_TIME;
	}
}

// �ˌ��p�^�[���̐؂�ւ�
void Enemy::ChangeShotPattern()
{
	// HP�̊����Ńp�^�[����ς���
	if ((m_life / m_maxLife) * 100 <= 70 && (m_life / m_maxLife) * 100 > 40)
	{
		m_shotType = WHORL_SHOT;
	}
	if ((m_life / m_maxLife) * 100 <= 40)
	{
		m_shotType = ALL_DIRECTION_SHOT;
	}
}

// �v���C���[�̕���������
void Enemy::TurnToDirectionPlayer()
{
	// �v���C���[�̕�������
	DirectX::SimpleMath::Vector3 m_dir;
	m_dir = m_playerPos - m_position;
	m_dir.Normalize();
	m_enemyAngle = atan2(m_dir.x, m_dir.z);
}

// �e������
void Enemy::Shot()
{
	m_shotInterval++;
	switch (m_shotType)
	{
	case NORMAL_SHOT: // �ʏ�
	{
		if (m_shotInterval > NORMAL_SHOT_INTERVEL)
		{
			// �e�̐���
			m_pBulletManager->CreateBullet(m_position, BULLET_SPEED, m_enemyAngle, m_pBulletManager->GetBulletGeometry(BulletManager::SPHERE), "SPHERE");

			m_shotInterval = 0;

			break;
		}
	}
	case ALL_DIRECTION_SHOT: // �S����
	{
		if (m_shotInterval > ALL_DIRECTION_SHOT_INTERVEL)
		{
			for (int rad = 0; rad < 130; rad += 6)
			{
				// �e�̐���
				m_pBulletManager->CreateBullet(m_position, BULLET_SPEED, (float)rad + m_enemyAngle, m_pBulletManager->GetBulletGeometry(BulletManager::SPHERE), "SPHERE");

				m_shotInterval = 0;
			}
		}
		break;
	}
	case WHORL_SHOT:

		if (m_shotInterval > WHORL_SHOT_INTERVEL)
		{
			for (int i = 0; i < 5; i++)
			{
				// �e�̐���
				m_pBulletManager->CreateBullet(m_position, BULLET_SPEED, m_shotRotate, m_pBulletManager->GetBulletGeometry(BulletManager::SPHERE), "SPHERE");

				m_shotRotate += 0.2f;
				m_shotInterval = 0;
				i++;
			}
		}
		break;
	default:
		break;
	}
}

// �Փ˂�����
void Enemy::OnCollision()
{
	// HP�����炷
	m_life--;

	m_hitFlag = true;
}