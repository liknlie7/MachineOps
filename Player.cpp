#include "pch.h"

#include "Player.h"
#include "Bullet.h"

const DirectX::SimpleMath::Vector3 Player::RANGE_MIN = DirectX::SimpleMath::Vector3(-18.5f, 0.0f, -19.0f);
const DirectX::SimpleMath::Vector3 Player::RANGE_MAX = DirectX::SimpleMath::Vector3(18.0f, 0.0f, 19.8f);


// TODO:�X�e�[�g�Ǘ��ɂ���
// TODO: �^�O����

// �R���X�g���N�^
Player::Player()
	: m_state(STATE_NORMAL)
	, m_mousePos(0.0f, 0.0f, 0.0f)
	, m_shotInterval(15.0f)
	, m_hitFlag(false)
	, m_blinkTime(30)
	, m_angle(0.0f)
	, m_isShiftDown(false)
	, m_life(1)
	, m_activeFlag(true)
	, m_accel(0.0f, 0.0f, 0.0f)
{
	// ����̍쐬
	//m_pWeapon = std::make_unique<Weapon>();

	// �v���C���[���f����shared_ptr���󂯎��
	m_pPlayer = std::weak_ptr<DirectX::Model>(ResourceManager::GetInstance()->GetModel(L"Resources/Models/tank.cmo"));

	// �T�E���h��shared_ptr���󂯎��
	//m_pSound = std::weak_ptr<Adx2Le>(ResourceManager::GetInstance()->GetSound(L"Resources\\Sounds\\PlayScene"));
}


// �f�X�g���N�^
Player::~Player()
{
	//m_pSound.reset();
}

// ������
void Player::Initialize()
{
	// KeyboardStateTracker�I�u�W�F�N�g�𐶐����� 
	m_keyboardTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();

	// �R���C�_�[
	m_collider.radius = 1.0f;
	m_collider.center = m_position;

	// �e�̍쐬
	//m_pWeapon->Initialize();

	// �e�̔z����m�ۂ���
	//m_pBullets.resize(BulletManager::NUM_BULLET);
	

}

// �X�V
void Player::Update()
{
	// �L�[�{�[�h�̏�Ԃ��擾����
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	// �L�[�{�[�h�g���b�J�[���X�V����
	m_keyboardTracker->Update(keyState);

	// �}�E�X�̏�Ԃ��擾����
	DirectX::Mouse::State mouseState = DirectX::Mouse::Get().GetState();
	// �}�E�X�g���b�J�[���X�V����
	m_mouseTracker.Update(mouseState);

	// ���x������
	m_velocity = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

	if (keyState.IsKeyUp(DirectX::Keyboard::Keys::LeftShift)) m_isShiftDown = false;
	if (keyState.IsKeyDown(DirectX::Keyboard::Keys::LeftShift)) m_isShiftDown = true;

	if (!m_isShiftDown)
	{
		// W������
		if (keyState.W) m_velocity.z = -0.2f;
		// A������
		if (keyState.A) m_velocity.x = -0.2f;
		// S������
		if (keyState.S) m_velocity.z = +0.2f;
		// D������
		if (keyState.D) m_velocity.x = +0.2f;
	}
	else
	{
		// W������
		if (keyState.W) m_velocity.z = -0.1f;
		// A������
		if (keyState.A) m_velocity.x = -0.1f;
		// S������
		if (keyState.S) m_velocity.z = +0.1f;
		// D������
		if (keyState.D) m_velocity.x = +0.1f;

	}

	if (m_hitFlag)
		Blink();

	if (m_enemyHitFlag) {
		m_velocity = DirectX::SimpleMath::Vector3::Zero;
		m_enemyHitFlag = false;
	}

	// ���x���
	m_position += m_velocity;

	// �͈͊O����o�Ȃ��悤�ɂ���
	m_position.x = Clamp(m_position.x, RANGE_MIN.x, RANGE_MAX.x);
	m_position.z = Clamp(m_position.z, RANGE_MIN.z, RANGE_MAX.z);


	m_dir = m_mousePos - m_position;
	m_dir.Normalize();

	m_angle = atan2(m_dir.x, m_dir.z);
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(m_position));
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateRotationY(m_angle);

	m_matrix = rotate * trans;

	// �e�𔭎˂���
	m_shotInterval++;

	if (m_shotInterval > 7.0f)
	{
		// ���N���b�N
		if (mouseState.leftButton)
		{
			// �e�̐���
			//m_pWeapon->CreateBullet();

			// �ˌ����̍Đ�
			//if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
			//	sptr->Play(CRI_PLAYER_SHOT);
			
			//for (int i = 0; m_pBullets.size(); i++)
			//{
			//	// �e���g�p���łȂ��Ƃ�
			//	if (m_pBullets[i] == nullptr)
			//	{
			//		// �e�𔭎˂���
			//		m_pBullets[i] = m_pBulletManager->Create(m_position, DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.8f), m_angle);
			//	}
			//}

			m_shotInterval = 0;
		}
	}

	// ����̍X�V
	//m_pWeapon->SetAngle(m_angle);
	//m_pWeapon->SetPlayerPos(m_position);
	//m_pWeapon->Update();

	m_collider.center = m_position;

}

// �`��
void Player::Render(const DirectX::SimpleMath::Matrix& _view)
{
	ID3D11DeviceContext1* context = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	DirectX::CommonStates* state = GameContext::Get<DirectX::CommonStates>();
	DirectX::SimpleMath::Matrix proj = GameContext::Get<Projection>()->GetMatrix();

	// �v���C���[�`��
	if (m_blinkTime % 5 == 0)
		if (std::shared_ptr<DirectX::Model> sptr = m_pPlayer.lock())
		{
			sptr->Draw(context, *state, m_matrix, _view, proj);
		}

	// ����̕`��
	//m_pWeapon->Render(_view);
}

// ��n��
void Player::Finalize()
{

}

// �Փ�
void Player::OnCollision(GameObject* _object)
{
	_object;
}

// �Փ�
void Player::OnCollision()
{
	m_hitFlag = true;

	//m_life--;
}

// �G�l�~�[�Ƃ̏Փ�
void Player::OnCollisionEnemy(DirectX::SimpleMath::Vector3 _enemyPos)
{
	DirectX::SimpleMath::Vector3 v = m_position - _enemyPos;
	v.Length();

}

// �_��
void Player::Blink()
{
	m_blinkTime--;

	if (m_blinkTime < 0)
	{
		m_hitFlag = false;
		m_blinkTime = 30;
	}
}

void Player::AddForce(float angle, float force)
{
	// �i�s�����x�N�g��
	DirectX::SimpleMath::Vector3 dir(0.0f, 0.0f, -1.0f);

	// ���@�̌����x�N�g�������߂�
	DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::CreateRotationY(angle);
	dir = DirectX::SimpleMath::Vector3::Transform(dir, rotY);

	// �����x
	m_accel = dir * force;

	// ���x�ɉ����x�𑫂�
	m_velocity += m_accel;
}
