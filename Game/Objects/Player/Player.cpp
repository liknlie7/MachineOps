#include "../../pch.h"

#include <CommonStates.h>

#include "../../Manager/ResourceManager.h"
#include "../../Common/DeviceResources.h"
#include "../../Common/Utilities.h"
#include "../../Common/Projection.h"
#include "../../Common/GameContext.h"
#include "../../Sound/PlayerSound.h"
#include "../Bullet.h"
#include "Player.h"

// �ړ������͈�
const DirectX::SimpleMath::Vector3 Player::RANGE_MIN = DirectX::SimpleMath::Vector3(-18.5f, 0.0f, -19.0f);
const DirectX::SimpleMath::Vector3 Player::RANGE_MAX = DirectX::SimpleMath::Vector3(18.0f, 0.0f, 19.8f);

// �e�̑��x
const float Player::BULLET_SPEED = 0.8f;

// �e�����Ԋu
const float Player::SHOT_INTERVAL = 7.0f;

// �v���C���[�ړ����x
const float Player::MOVE_SPEED = 0.2f;

// �v���C���[�ړ����x(�V�t�g����)
const float Player::MOVE_SLOW_SPEED = 0.1f;

// �R���X�g���N�^
Player::Player()
	: m_mousePos(DirectX::SimpleMath::Vector3::Zero)
	, m_shotInterval(SHOT_INTERVAL)
	, m_hitFlag(false)
	, m_angle(0.0f)
	, m_isShiftDown(false)
{
	// �v���C���[���f����shared_ptr���󂯎��
	m_pPlayer = std::weak_ptr<DirectX::Model>(ResourceManager::GetInstance()->GetModel(L"Resources/Models/tank.cmo"));

	// �T�E���h��shared_ptr���󂯎��
	m_pSound = std::weak_ptr<Adx2Le>(ResourceManager::GetInstance()->GetSound(L"Resources\\Sounds\\PlayScene"));
}

// �f�X�g���N�^
Player::~Player()
{
	m_pSound.reset();
}

// ������
void Player::Initialize()
{
	// KeyboardStateTracker�I�u�W�F�N�g�𐶐����� 
	m_keyboardTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();

	// �R���C�_�[�ݒ�
	m_collider.radius = 1.0f;
	m_collider.center = m_position;
}

// �X�V
void Player::Update()
{
	// �ړ�
	Move();

	// �e������
	Shot();

	// �R���C�_�[�̒��S��ݒ�
	m_collider.center = m_position;
}

// �`��
void Player::Render(const DirectX::SimpleMath::Matrix& _view)
{
	ID3D11DeviceContext1* context = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	DirectX::CommonStates* state = GameContext::Get<DirectX::CommonStates>();
	DirectX::SimpleMath::Matrix proj = GameContext::Get<Projection>()->GetMatrix();

	// �v���C���[�`��
	if (std::shared_ptr<DirectX::Model> sptr = m_pPlayer.lock())
	{
		sptr->Draw(context, *state, m_matrix, _view, proj);
	}
}

// �Փ�
void Player::OnCollision()
{
	m_hitFlag = true;
}

// �ړ�
void Player::Move()
{
	// �L�[�{�[�h�̏�Ԃ��擾����
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	// �L�[�{�[�h�g���b�J�[���X�V����
	m_keyboardTracker->Update(keyState);

	// ���x������
	m_velocity = DirectX::SimpleMath::Vector3::Zero;

	if (keyState.IsKeyUp(DirectX::Keyboard::Keys::LeftShift)) m_isShiftDown = false;
	if (keyState.IsKeyDown(DirectX::Keyboard::Keys::LeftShift)) m_isShiftDown = true;

	if (!m_isShiftDown)
	{
		// W������
		if (keyState.W) m_velocity.z = -MOVE_SPEED;
		// A������
		if (keyState.A) m_velocity.x = -MOVE_SPEED;
		// S������
		if (keyState.S) m_velocity.z = +MOVE_SPEED;
		// D������
		if (keyState.D) m_velocity.x = +MOVE_SPEED;
	}
	else
	{
		// W������
		if (keyState.W) m_velocity.z = -MOVE_SLOW_SPEED;
		// A������
		if (keyState.A) m_velocity.x = -MOVE_SLOW_SPEED;
		// S������
		if (keyState.S) m_velocity.z = +MOVE_SLOW_SPEED;
		// D������
		if (keyState.D) m_velocity.x = +MOVE_SLOW_SPEED;
	}

	// ���x���
	m_position += m_velocity;

	// �͈͊O����o�Ȃ��悤�ɂ���
	m_position.x = Clamp(m_position.x, RANGE_MIN.x, RANGE_MAX.x);
	m_position.z = Clamp(m_position.z, RANGE_MIN.z, RANGE_MAX.z);

	// �������v�Z
	m_dir = m_mousePos - m_position;
	m_dir.Normalize();

	// �}�E�X�̕��֌�����
	m_angle = atan2(m_dir.x, m_dir.z);
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(m_position));
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateRotationY(m_angle);

	m_matrix = rotate * trans;
}

// �e������
void Player::Shot()
{
	// �}�E�X�̏�Ԃ��擾����
	DirectX::Mouse::State mouseState = DirectX::Mouse::Get().GetState();

	// �}�E�X�g���b�J�[���X�V����
	m_mouseTracker.Update(mouseState);

	// �e�𔭎˂���
	m_shotInterval++;

	if (m_shotInterval > SHOT_INTERVAL)
	{
		// ���N���b�N
		if (mouseState.leftButton)
		{
			// �e�̐���
			m_pBulletManager->CreateBullet(m_position, BULLET_SPEED, m_angle, m_pBulletManager->GetBulletGeometry(BulletManager::BOX), "BOX");

			// �ˌ����̍Đ�
			if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
			{
				sptr->Play(CRI_PLAYER_SHOT);
			}

			m_shotInterval = 0;
		}
	}
}