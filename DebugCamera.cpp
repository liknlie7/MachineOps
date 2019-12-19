#include "pch.h"

#include "DebugCamera.h"

// �f�t�H���g����
const float DebugCamera::DEFAULT_CAMERA_DISTANCE = 5.0f;

// �R���X�g���N�^
DebugCamera::DebugCamera()
	: m_yAngle(0.0f)
	, m_xAngle(0.0f)
	, m_prevX(0), m_prevY(0)
	, m_scrollWheelValue(0)
{
}

// �f�X�g���N�^
DebugCamera::~DebugCamera()
{
}

// �X�V
void DebugCamera::update()
{
	// �}�E�X�̎擾
	auto state = DirectX::Mouse::Get().GetState();

	// ���΃��[�h�Ȃ牽�����Ȃ�
	if (state.positionMode == DirectX::Mouse::MODE_RELATIVE) return;

	// �g���b�J�[�X�V
	m_tracker.Update(state);

	// �}�E�X�̍��{�^���������ꂽ
	if (m_tracker.leftButton == DirectX::Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		// �}�E�X�̍��W���擾
		m_prevX = state.x;
		m_prevY = state.y;
	}

	// �}�E�X�̃{�^����������Ă�����J�������ړ�������
	if (state.leftButton)
	{
		motion(state.x, state.y);
	}
	// �}�E�X�̍��W��O��̂Ƃ��ĕۑ�
	m_prevX = state.x;
	m_prevY = state.y;

	// �}�E�X�̃t�H�C�[���l���擾
	m_scrollWheelValue = state.scrollWheelValue;
	if (m_scrollWheelValue > 0)
	{
		m_scrollWheelValue = 0;
		DirectX::Mouse::Get().ResetScrollWheelValue();
	}

	// �r���[�s����Z�o����
	DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::CreateRotationY(m_yAngle);
	DirectX::SimpleMath::Matrix rotX = DirectX::SimpleMath::Matrix::CreateRotationX(m_xAngle);

	DirectX::SimpleMath::Matrix rt = rotY * rotX;

	DirectX::SimpleMath::Vector3 eye(0.0f, 2.0f, 2.0f);
	DirectX::SimpleMath::Vector3 target(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

	eye = DirectX::SimpleMath::Vector3::Transform(eye, rt.Invert());
	eye *= (DEFAULT_CAMERA_DISTANCE - m_scrollWheelValue / 100);
	up = DirectX::SimpleMath::Vector3::Transform(up, rt.Invert());

	m_eye = eye;
	m_target = target;

	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(eye, target, up);
}

// �s��̐���
void DebugCamera::motion(int x, int y)
{
	// �}�E�X�|�C���^�̑O�񂩂�̕ψ�
	float dx = static_cast<float>(x - m_prevX);
	float dy = static_cast<float>(y - m_prevY);

	if (dx != 0.0f || dy != 0.0f)
	{
		// �x���̉�]
		float yAngle = dx * DirectX::XM_PI / 180.0f;
		// �w���̉�]
		float xAngle = dy * DirectX::XM_PI / 180.0f;

		m_xAngle += xAngle;
		m_yAngle += yAngle;
	}
}