#include "pch.h"
#include "Enemy.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// �R���X�g���N�^
Enemy::Enemy()
	: m_decisionAreaPos(5.0f, 1.0f, 0.0f)
	, m_blinkTime(50)
	, m_hitFlag(false)
{
}

// �f�X�g���N�^
Enemy::~Enemy()
{
}

// �m�[�}���^������
void Enemy::InitializeNormal(DirectX::SimpleMath::Vector3 _pos)
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>().Get();

	// �����蔻��p
	m_pDecisionArea = GeometricPrimitive::CreateSphere(deviceResources->GetD3DDeviceContext(), 2.0f);

	// �G�t�F�N�g�t�@�N�g���̍쐬 
	EffectFactory* factory = new EffectFactory(deviceResources->GetD3DDevice());
	// �e�N�X�`���̓ǂݍ��݃p�X�w�� 
	factory->SetDirectory(L"Resources/Models");
	// �t�@�C�����w�肵�ă��f���f�[�^�ǂݍ��� 
	m_pEnemy = Model::CreateFromCMO(
		deviceResources->GetD3DDevice(),
		L"Resources/Models/Enemy1.cmo",
		*factory
	);
	delete factory;

	m_pos = _pos;
	// �����̏�����
	m_speed = 0.08f;

	m_life = 3;

}

// ������������
void Enemy::InitializeShield(DirectX::SimpleMath::Vector3 _pos)
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>().Get();

	// �����蔻��p
	m_pDecisionArea = GeometricPrimitive::CreateSphere(deviceResources->GetD3DDeviceContext(), 2.0f);

	// �G�t�F�N�g�t�@�N�g���̍쐬 
	EffectFactory* factory = new EffectFactory(deviceResources->GetD3DDevice());
	// �e�N�X�`���̓ǂݍ��݃p�X�w�� 
	factory->SetDirectory(L"Resources/Models");
	// �t�@�C�����w�肵�ă��f���f�[�^�ǂݍ��� 
	m_pEnemy = Model::CreateFromCMO(
		deviceResources->GetD3DDevice(),
		L"Resources/Models/Enemy2.cmo",
		*factory
	);
	delete factory;

	m_pos = _pos;
	// �����̏�����
	m_speed = 0.05f;

	m_life = 5;
}

// �X�V
void Enemy::UpdateNormal(Vector3 _playerPos)
{
	ChasePlayer(_playerPos);
	if (m_hitFlag)
	{
		Blink();
	}
	// ���x���
	m_pos += m_vel;

	Vector3 m_dir;
	m_dir = _playerPos - m_pos;
	m_dir.Normalize();
	float angle = atan2(m_dir.x, m_dir.z);
	Matrix rotate = Matrix::CreateRotationY(angle);
	Matrix scale = Matrix::CreateScale(1.5f);
	m_mat = scale * rotate * Matrix::CreateTranslation(Vector3(m_pos.x, 1.0f, m_pos.z));
}

void Enemy::UpdateShield(Vector3 _playerPos)
{
	if (m_hitFlag)
	{
		Blink();
	}
	Vector3 m_dir;
	m_dir = _playerPos - m_pos;
	m_dir.Normalize();
	float angle = atan2(m_dir.x, m_dir.z);
	Matrix rotate = Matrix::CreateRotationY(angle);
	Matrix scale = Matrix::CreateScale(1.5f);
	m_mat = scale * rotate * Matrix::CreateTranslation(Vector3(m_pos.x, 1.0f, m_pos.z));


}

// �`��
void Enemy::Render(Matrix _view, Vector4 _color)
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>().Get();
	CommonStates* state = GameContext<CommonStates>().Get();
	Projection* proj = GameContext<Projection>().Get();

	// ���f���`��
	if (m_life > 0)
		if (m_blinkTime % 5 == 0)
			m_pEnemy->Draw(deviceResources->GetD3DDeviceContext(), *state, m_mat, _view, proj->GetMatrix());

	// ����p
	//m_pDecisionArea->Draw(m_mat, _view, _proj, _color, nullptr, true);
}

// ��n��
void Enemy::Finalize()
{

}

// �v���C���[��ǂ�������
void Enemy::ChasePlayer(Vector3 _playerPos)
{
	// �v���C���[�ւ̌������v�Z
	Vector3 dir = _playerPos - m_pos;
	dir.Normalize();

	// �G�̈ړ�
	m_pos += dir * m_speed;
}

// �_��
void Enemy::Blink()
{
	m_blinkTime--;

	if (m_blinkTime < 0)
	{
		m_hitFlag = false;
		m_blinkTime = 50;
	}
}