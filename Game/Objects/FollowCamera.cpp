#include "../../pch.h"

#include "../Common/Utilities.h"
#include "../Common/GameContext.h"
#include "../Common/DeviceResources.h"
#include "FollowCamera.h"

// ���_
const DirectX::SimpleMath::Vector3 FollowCamera::EYE_VEC = DirectX::SimpleMath::Vector3(0.0f, 30.0f, 0.0f);

// �J�����̌���
const DirectX::SimpleMath::Vector3 FollowCamera::UP_VEC = DirectX::SimpleMath::Vector3(0.0f, 0.0f, -1.0f);

// �ړ������͈�
const DirectX::SimpleMath::Vector3 FollowCamera::RANGE_MIN = DirectX::SimpleMath::Vector3(-5.0f, 0.0f, -9.0f);
const DirectX::SimpleMath::Vector3 FollowCamera::RANGE_MAX = DirectX::SimpleMath::Vector3(5.0f, 0.0f, 10.0f);

// �R���X�g���N�^
FollowCamera::FollowCamera()
{
	// ���_�ݒ�
	m_eye = EYE_VEC;

	// �����_�ݒ�
	m_target = DirectX::SimpleMath::Vector3::Zero;

	// �J������ʐݒ�
	m_up = UP_VEC;

	// �r���[�|�[�g�̍쐬
	RECT size = GameContext::Get<DX::DeviceResources>()->GetOutputSize();
	m_viewPort =
		DirectX::SimpleMath::Matrix::CreateScale(DirectX::SimpleMath::Vector3(0.5f, -0.5f, 1.0f)) *
		DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(0.5f, 0.5f, 0.0f)) *
		DirectX::SimpleMath::Matrix::CreateScale(DirectX::SimpleMath::Vector3(float(size.right), float(size.bottom), 1.0f));
}

// ������
void FollowCamera::Initialize()
{
	// ���E�̍쐬
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
}

// �X�V
void FollowCamera::Update(DirectX::SimpleMath::Vector3 _eye, DirectX::SimpleMath::Vector3 _target)
{
	// �X�e�[�W�O�ɍs���Ȃ��悤�ɔ͈͂𐧌�
	_target.x = Clamp(_target.x, RANGE_MIN.x, RANGE_MAX.x);
	_target.z = Clamp(_target.z, RANGE_MIN.z, RANGE_MAX.z);
	_eye.x = Clamp(_eye.x, RANGE_MIN.x, RANGE_MAX.x);
	_eye.z = Clamp(_eye.z, RANGE_MIN.z, RANGE_MAX.z);

	// ���E�̍X�V
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(_eye, _target, m_up);
}