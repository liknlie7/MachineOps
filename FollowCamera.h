#pragma once
#include <d3d11_1.h>
#include <SimpleMath.h>

#include "GameContext.h"
#include "DeviceResources.h"

// �ǔ��J����
class FollowCamera
{
public: // ��{

	// �R���X�g���N�^
	FollowCamera();

public: // �A�N�Z�T

	// �r���[�s��擾
	DirectX::SimpleMath::Matrix GetViewMatrix() const
	{
		return m_view;
	}

	// �����_�̐ݒ�
	void SetTargetPosition(const DirectX::SimpleMath::Vector3& target)
	{
		m_target = target;
	}

	// ���_�̐ݒ�
	void SetEyePosition(const DirectX::SimpleMath::Vector3& eye)
	{
		m_eye = eye;
	}

	// ViewPort�̎擾
	DirectX::SimpleMath::Matrix GetViewPort()
	{
		return m_viewPort;
	}

public: // �֐�

	// ������
	void Initialize();
	// �X�V
	void Update(DirectX::SimpleMath::Vector3 _eye, DirectX::SimpleMath::Vector3 _target);

private: // �T�u�֐�

	void Shake(float _duration, float _magnitude);

	void DoShake(float _duration, float _magnitude);

public: // �萔

	// ���_
	static const DirectX::SimpleMath::Vector3 EYE_VEC;
	// �J������
	static const DirectX::SimpleMath::Vector3 UP_VEC;
	// �ړ������͈�
	static const DirectX::SimpleMath::Vector3 RANGE_MIN;
	static const DirectX::SimpleMath::Vector3 RANGE_MAX;


private: // �ϐ�

	DirectX::SimpleMath::Matrix m_view;

	// ���_
	DirectX::SimpleMath::Vector3 m_eye;
	// �����_
	DirectX::SimpleMath::Vector3 m_target;
	DirectX::SimpleMath::Vector3 m_up;

	// ViewPort
	DirectX::SimpleMath::Matrix							m_viewPort;

};