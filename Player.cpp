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
	, m_blinkTime(50)
	, m_angle(0.0f)
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
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	m_context = deviceResources->GetD3DDeviceContext();

	// KeyboardStateTracker�I�u�W�F�N�g�𐶐����� 
	m_keyboardTracker = std::make_unique<Keyboard::KeyboardStateTracker>();

	// �G�t�F�N�g�t�@�N�g���̍쐬 
	EffectFactory* factory = new EffectFactory(deviceResources->GetD3DDevice());
	// �e�N�X�`���̓ǂݍ��݃p�X�w�� 
	factory->SetDirectory(L"Resources/Models");
	// �t�@�C�����w�肵�ă��f���f�[�^�ǂݍ��� 
	m_pPlayer = Model::CreateFromCMO(
		deviceResources->GetD3DDevice(),
		L"Resources/Models/tank.cmo",
		*factory
	);
	delete factory;

	// �e�̍쐬
	m_pWeapon->Initialize();

	m_collider.radius = 1.0f;
	m_collider.center = m_pos;
	
	// �����蔻��p
	//m_pDecisionArea = GeometricPrimitive::CreateSphere(deviceResources->GetD3DDeviceContext(), 2.0f);

	//m_decisionAreaPos = m_pos;

}

// �X�V
void Player::Update(DX::StepTimer const& timer)
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

	// W������
	if (keyState.W) m_vel.z = -0.2f;
	// A������
	if (keyState.A) m_vel.x = -0.2f;
	// S������
	if (keyState.S) m_vel.z = +0.2f;
	// D������
	if (keyState.D) m_vel.x = +0.2f;
	// Space������
	//if (keyState.Space && m_pos.y == 0.5f) { m_vel.y = 0.5f; }

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
	m_pWeapon->Update(timer);

	m_collider.center = m_pos;  

}

// �`��
void Player::Render(const Matrix& _view)
{
	Projection* proj = GameContext<Projection>().Get();
	CommonStates* state = GameContext<CommonStates>().Get();

	// �v���C���[�`��
	if (m_blinkTime % 5 == 0)
		m_pPlayer->Draw(m_context, *state, m_mat, _view, proj->GetMatrix());

	// ����̕`��
	m_pWeapon->Render(_view);

	// ����p
	//m_pDecisionArea->Draw(m_mat, _view, proj->GetMatrix(), Colors::Red, nullptr, true);

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
		m_blinkTime = 50;
	}
}