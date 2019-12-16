#include "pch.h"

#include "Player.h"
#include "Bullet.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using namespace std;

// �R���X�g���N�^
Player::Player()
	: m_mousePos(0.0f, 0.0f, 0.0f)
	, m_shotInterval(15.0f)
	, m_hitFlag(false)
	, m_blinkTime(30)
	, m_angle(0.0f)
	, m_isShiftDown(false)
{
	m_pWeapon = make_unique<Weapon>();
}


// �f�X�g���N�^
Player::~Player()
{
}

// ������
void Player::Initialize()
{
	// KeyboardStateTracker�I�u�W�F�N�g�𐶐����� 
	m_keyboardTracker = std::make_unique<Keyboard::KeyboardStateTracker>();

	// ���f���쐬 
	EffectFactory* factory = new EffectFactory(GameContext::Get<DX::DeviceResources>()->GetD3DDevice());
	factory->SetDirectory(L"Resources/Models");
	m_pPlayer = Model::CreateFromCMO(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources/Models/tank.cmo", *factory);
	delete factory;

	// �R���C�_�[
	m_collider.radius = 1.0f;
	m_collider.center = m_pos;

	// �e�̍쐬
	m_pWeapon->Initialize();
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
	m_vel = Vector3(0.0f, 0.0f, 0.0f);

	if (keyState.IsKeyUp(DirectX::Keyboard::Keys::LeftShift)) m_isShiftDown = false;
	if (keyState.IsKeyDown(DirectX::Keyboard::Keys::LeftShift)) m_isShiftDown = true;

	if (!m_isShiftDown)
	{
		// W������
		if (keyState.W) m_vel.z = -0.2f;
		// A������
		if (keyState.A) m_vel.x = -0.2f;
		// S������
		if (keyState.S) m_vel.z = +0.2f;
		// D������
		if (keyState.D) m_vel.x = +0.2f;
	}
	else
	{
		// W������
		if (keyState.W) m_vel.z = -0.1f;
		// A������
		if (keyState.A) m_vel.x = -0.1f;
		// S������
		if (keyState.S) m_vel.z = +0.1f;
		// D������
		if (keyState.D) m_vel.x = +0.1f;

	}

	if (m_hitFlag)  Blink();

	// ���x���
	m_pos += m_vel;

	m_dir = m_mousePos - m_pos;
	m_dir.Normalize();

	m_angle = atan2(m_dir.x, m_dir.z);
	Matrix trans = Matrix::CreateTranslation(Vector3(m_pos));
	Matrix rotate = Matrix::CreateRotationY(m_angle);

	m_mat = rotate * trans;

	// �e�𔭎˂���
	m_shotInterval++;
	
	if (m_shotInterval > 15.0f)
	{
		// ���N���b�N
		if (mouseState.leftButton)
		{
			// �e�̐���
			m_pWeapon->CreateBullet();
			m_shotInterval = 0;
		}
	}

	// ����̍X�V
	m_pWeapon->SetAngle(m_angle);
	m_pWeapon->SetPlayerPos(m_pos);
	m_pWeapon->Update();

	m_collider.center = m_pos;

}

// �`��
void Player::Render(const Matrix& _view)
{
	// �v���C���[�`��
	if (m_blinkTime % 5 == 0)
		m_pPlayer->Draw(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(),
			*GameContext::Get<CommonStates>(), m_mat, _view, GameContext::Get<Projection>()->GetMatrix());

	// ����̕`��
	m_pWeapon->Render(_view);
}

// ��n��
void Player::Finalize()
{

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