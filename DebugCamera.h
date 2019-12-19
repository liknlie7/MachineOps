#pragma once

#include "SimpleMath.h"
#include "Mouse.h"

// �f�o�b�O�J����
class DebugCamera
{
public: // ��{

	// �R���X�g���N�^
	DebugCamera();

	// �f�X�g���N�^
	~DebugCamera();

public: //�A�N�Z�T

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

public: // �֐�

	// �X�V
	void update();

private: // �T�u�֐�

	void motion(int x, int y);

public: // �萔

	// �J�����̋���
	static const float DEFAULT_CAMERA_DISTANCE;

private: // �ϐ�

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