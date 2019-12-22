#pragma once
#include <d3d11_1.h>
#include <SimpleMath.h>


// �ǔ��J����
class FollowCamera
{
public: // ��{

	// �R���X�g���N�^
	FollowCamera();

public: // �A�N�Z�T

	// �r���[�s��擾
	DirectX::SimpleMath::Matrix getViewMatrix() const
	{
		return m_view;
	}

	// �����_�̐ݒ�
	void FollowCamera::SetTargetPosition(const DirectX::SimpleMath::Vector3& target)
	{
		m_target = target;
	}

	// ���_�̐ݒ�
	void FollowCamera::SetEyePosition(const DirectX::SimpleMath::Vector3& eye)
	{
		m_eye = eye;
	}

public: // �֐�

	// ������
	void Initialize();
	// �X�V
	void Update(DirectX::SimpleMath::Vector3 _eye, DirectX::SimpleMath::Vector3 _target);

	void Shake(float _duration, float _magnitude);

	void DoShake(float _duration, float _magnitude);

public: // �萔

	// ���_
	static const DirectX::SimpleMath::Vector3 EYE_VEC;
	// �J������
	static const DirectX::SimpleMath::Vector3 UP_VEC;

private: // �ϐ�

	DirectX::SimpleMath::Matrix m_view;

	// ���_
	DirectX::SimpleMath::Vector3 m_eye;
	// �����_
	DirectX::SimpleMath::Vector3 m_target;
	DirectX::SimpleMath::Vector3 m_up;
};