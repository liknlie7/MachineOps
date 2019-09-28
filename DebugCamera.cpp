#include "pch.h"

#include "DebugCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float DebugCamera::DEFAULT_CAMERA_DISTANCE = 5.0f;


DebugCamera::DebugCamera()
	: m_yAngle(0.0f)
	, m_xAngle(0.0f)
	, m_prevX(0), m_prevY(0)
	, m_scrollWheelValue(0)
{
}


DebugCamera::~DebugCamera()
{
}


void DebugCamera::update()
{
	auto state = Mouse::Get().GetState();

	// ���΃��[�h�Ȃ牽�����Ȃ�
	if (state.positionMode == Mouse::MODE_RELATIVE) return;

	m_tracker.Update(state);

	// �}�E�X�̍��{�^���������ꂽ
	if (m_tracker.leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
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
		Mouse::Get().ResetScrollWheelValue();
	}

	// �r���[�s����Z�o����
	Matrix rotY = Matrix::CreateRotationY(m_yAngle);
	Matrix rotX = Matrix::CreateRotationX(m_xAngle);

	Matrix rt = rotY * rotX;

	Vector3 eye(0.0f, 2.0f, 2.0f);
	Vector3 target(0.0f, 0.0f, 0.0f);
	Vector3 up(0.0f, 1.0f, 0.0f);

	eye = Vector3::Transform(eye, rt.Invert());
	eye *= (DEFAULT_CAMERA_DISTANCE - m_scrollWheelValue / 100);
	up = Vector3::Transform(up, rt.Invert());

	m_eye = eye;
	m_target = target;

	m_view = Matrix::CreateLookAt(eye, target, up);
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
		float yAngle = dx * XM_PI / 180.0f;
		// �w���̉�]
		float xAngle = dy * XM_PI / 180.0f;

		m_xAngle += xAngle;
		m_yAngle += yAngle;
	}
}