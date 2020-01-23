#include "pch.h"

#include "Enemy.h"
#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using namespace std;

// �ʏ�̑傫��
const float Enemy::SIZE = 1.5f;

// �{�X�̑傫��
const float Enemy::BOSS_SIZE = 8.0f;

// �R���X�g���N�^
Enemy::Enemy(const int _type, const std::string& _tag)
	: GameObject(_tag)
	, m_blinkTime(30)
	, m_isValid(false)
	, m_playerPos(0.0f, 0.0f, 0.0f)
	, m_life(100)
	, m_maxLife(100)
	, m_wayNum(3)
	, m_changeAngle(30)
	, m_bulletEndAngle(0)
	, m_shotInterval(10.0f)
	, m_shotRotate(0.0f)
{
	m_enemyType = _type;
}

// �f�X�g���N�^
Enemy::~Enemy()
{
}

void Enemy::Initialize(DirectX::SimpleMath::Vector3 _pos)
{

	// �G�t�F�N�g�t�@�N�g���̍쐬 
	EffectFactory* factory = new EffectFactory(GameContext::Get<DX::DeviceResources>()->GetD3DDevice());

	// �e�̌`��쐬
	m_pBulletGeometric = GeometricPrimitive::CreateSphere(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(), 0.3f);

	// �e�N�X�`���̓ǂݍ��݃p�X�w�� 
	factory->SetDirectory(L"Resources/Models");

	switch (m_enemyType)
	{

	case NORMAL_ENEMY: // �m�[�}���^�C�v

		// ���f���f�[�^�ǂݍ��� 
		m_pEnemy = Model::CreateFromCMO(
			GameContext::Get<DX::DeviceResources>()->GetD3DDevice(),
			L"Resources/Models/Enemy1.cmo",
			*factory
		);
		delete factory;

		m_position = _pos;
		// �����̏�����
		m_speed = 0.08f;

		m_life = 300;

		m_collider.radius = 2.0f;
		m_collider.center = m_position;
		//m_decisionAreaPos = m_pos;

		m_shotType = NORMAL_SHOT;
		break;

		// ������
	case SHIELD_ENEMY:

		// ���f���f�[�^�ǂݍ��� 
		m_pEnemy = Model::CreateFromCMO(
			GameContext::Get<DX::DeviceResources>()->GetD3DDevice(),
			L"Resources/Models/Enemy2.cmo",
			*factory
		);
		delete factory;

		m_position = _pos;
		// �����̏�����
		m_speed = 0.05f;

		m_life = 5;

		m_collider.radius = 2.0f;
		m_collider.center = m_position;
		//m_decisionAreaPos = m_pos;
		m_shotType = 4;

		break;

	case BOSS_ENEMY:
		// ���f���f�[�^�ǂݍ��� 
		m_pEnemy = Model::CreateFromCMO(
			GameContext::Get<DX::DeviceResources>()->GetD3DDevice(),
			L"Resources/Models/Enemy1.cmo",
			*factory
		);
		delete factory;

		m_position = _pos;
		// �����̏�����
		m_speed = 0.08f;

		m_life = m_maxLife;
		m_shotType = NORMAL_SHOT;
		m_collider.radius = /*2.0f*/5.0f;
		m_collider.center = m_position;
		//m_decisionAreaPos = m_pos;

		break;
	}

}

// �X�V
void Enemy::Update()
{
	Vector3 m_dir;
	m_dir = m_playerPos - m_position;
	m_dir.Normalize();
	m_enemyAngle = atan2(m_dir.x, m_dir.z);

	switch (m_enemyType)
	{
	case NORMAL_ENEMY:

		ChasePlayer(m_playerPos);

		m_bulletEndAngle -= 180 + m_wayNum / 2 * m_changeAngle;

		for (int i = 0; i < m_wayNum; i++)
		{
			CreateBullet();
		}

		break;
	case SHIELD_ENEMY:

		break;
	case BOSS_ENEMY:



		m_playerPos.Normalize();
		Vector3 baseDir = m_playerPos;


		break;
	}

	if (m_life <= 80 && m_life > 50)
		m_shotType = WHORL_SHOT;
	if (m_life <= 50)
		m_shotType = ALL_DIRECTION_SHOT;

	m_shotInterval++;
	switch (m_shotType)
	{
	case NORMAL_SHOT:
	{
		if (m_shotInterval > 15.0f)
		{
			m_pBullets.push_back(make_unique<Bullet>(m_position + Vector3(0.0f, 0.1f, 0.0f), m_enemyAngle, Vector3(0.0f, 0.0f, 0.15f), "EnemyBullet"));
			CreateBullet();
			m_shotInterval = 0;

			break;
		}
	}
	case ALL_DIRECTION_SHOT:
	{
		if (m_shotInterval > 15.0f)
		{
			for (int rad = 0; rad < 130; rad += 6)
			{
				m_pBullets.push_back(make_unique<Bullet>(m_position + Vector3(0.0f, 0.1f, 0.0f), (float)rad + m_enemyAngle, Vector3(0.0f, 0.0f, 0.15f), "EnemyBullet"));
				CreateBullet();
				m_shotInterval = 0;
			}
		}
		break;
	}
	case WHORL_SHOT:
		if (m_shotInterval > 5.0f)
		{

			int i = 0;
			while (i < 5)
			{
				m_pBullets.push_back(make_unique<Bullet>(m_position + Vector3(0.0f, 0.1f, 0.0f), m_shotRotate, Vector3(0.0f, 0.0f, 0.15f),"EnemyBullet"));
				CreateBullet();
				m_shotRotate += 0.2f;
				m_shotInterval = 0;
				i++;
			}
		}
		break;
	default:
		break;
	}
	// ���x���
	m_position += m_velocity;

	for (vector<unique_ptr<Bullet>>::iterator itr = m_pBullets.begin(); itr != m_pBullets.end(); itr++)
	{
		(*itr)->Update();
	}


	Matrix rotate = Matrix::CreateRotationY(m_enemyAngle);
	Matrix scale = Matrix::CreateScale(BOSS_SIZE);
	m_matrix = scale * rotate * Matrix::CreateTranslation(Vector3(m_position.x, 1.0f, m_position.z));

	m_collider.center = m_position;

	if (m_life == 0)
		m_pEnemy = nullptr;

	OutRangeBullet();
	if (m_isValid)  Blink();

}


// �`��
void Enemy::Render(const Matrix& _view)
{
	// ���f���`��
	if (m_blinkTime % 5 == 0)
		if (m_life != 0)
			m_pEnemy->Draw(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(), *GameContext::Get<CommonStates>(), m_matrix, _view, GameContext::Get<Projection>()->GetMatrix());

	// �e�`��
	for (vector<unique_ptr<Bullet>>::iterator itr = m_pBullets.begin(); itr != m_pBullets.end(); itr++)
	{
		(*itr)->Render(_view);
	}
}

// ��n��
void Enemy::Finalize()
{

}

// �v���C���[��ǂ�������
void Enemy::ChasePlayer(Vector3 _playerPos)
{
	// �v���C���[�ւ̌������v�Z
	Vector3 dir = _playerPos - m_position;
	dir.Normalize();

	// �G�̈ړ�
	m_position += dir * m_speed;
}

// �_��
void Enemy::Blink()
{
	m_blinkTime--;

	if (m_blinkTime < 0)
	{
		m_isValid = false;
		m_blinkTime = 30;
	}
}

// �Փ˂�����
void Enemy::OnCollision()
{
	m_life--;

	m_isValid = true;
}

// �e�̍쐬
void Enemy::CreateBullet()
{
	for (vector<unique_ptr<Bullet>>::iterator itr = m_pBullets.begin(); itr != m_pBullets.end(); itr++)
	{
		(*itr)->Initialize(m_pBulletGeometric.get());
	}
}

// �e���Փ˂�����
void Enemy::BulletOnCollision(int _number)
{
	m_pBullets[_number]->SetIsValid(false);

	vector<unique_ptr<Bullet>>::iterator itr = m_pBullets.begin();
	while (itr != m_pBullets.end())
	{
		if (!(*itr)->GetIsValid())
			itr = m_pBullets.erase(itr);
		else
			++itr;
	}
}

// �͈͊O�ɏo����
void Enemy::OutRangeBullet()
{
	vector<unique_ptr<Bullet>>::iterator itr = m_pBullets.begin();

	while (itr != m_pBullets.end())
	{
		if ((*itr)->GetLife() < 0.0f)
			itr = m_pBullets.erase(itr);
		else
			++itr;
	}
}