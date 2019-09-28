#pragma once

#include "SimpleMath.h"
#include "Mouse.h"


class DebugCamera
{
public:

	// �J�����̋���
	static const float DEFAULT_CAMERA_DISTANCE;

public:

	DebugCamera();
	~DebugCamera();

public:

	void update();

public:

	// �r���[�s��擾
	DirectX::SimpleMath::Matrix getViewMatrix()
	{
		return m_view;
	}

	// �ʒu�擾
	DirectX::SimpleMath::Vector3 getEyePosition()
	{
		return m_eye;
	}

	// �����_�擾
	DirectX::SimpleMath::Vector3 getTargetPosition()
	{
		return m_target;
	}

private:

	void motion(int x, int y);

private:

	// ����]
	float m_yAngle;
	// �c��]
	float m_xAngle;

	// �O��̃}�E�X���W
	int m_prevX, m_prevY;

	// �������ꂽ�r���[�s��
	DirectX::SimpleMath::Matrix m_view;

	// �X�N���[���t�H�C�[���l
	int m_scrollWheelValue;

	// ���_
	DirectX::SimpleMath::Vector3 m_eye;

	// �����_
	DirectX::SimpleMath::Vector3 m_target;

	// �}�E�X�g���b�J�[
	DirectX::Mouse::ButtonStateTracker m_tracker;
};