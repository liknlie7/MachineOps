#include "pch.h"

#include "FollowCamera.h"

#include <random>
#include <time.h>

#include "Utilities.h"

// 視点
const DirectX::SimpleMath::Vector3 FollowCamera::EYE_VEC = DirectX::SimpleMath::Vector3(0.0f, 30.0f, 0.0f);
// カメラの向き
const DirectX::SimpleMath::Vector3 FollowCamera::UP_VEC = DirectX::SimpleMath::Vector3(0.0f, 0.0f, -1.0f);
// 移動制限範囲
const DirectX::SimpleMath::Vector3 FollowCamera::RANGE_MIN = DirectX::SimpleMath::Vector3(-5.0f, 0.0f, -9.0f);
const DirectX::SimpleMath::Vector3 FollowCamera::RANGE_MAX = DirectX::SimpleMath::Vector3(5.0f, 0.0f, 10.0f);



FollowCamera::FollowCamera()
{
	m_eye = EYE_VEC;
	m_target = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	m_up = UP_VEC;

	// ビューポートの作成
	RECT size = GameContext::Get<DX::DeviceResources>()->GetOutputSize();
	m_viewPort =
		DirectX::SimpleMath::Matrix::CreateScale(DirectX::SimpleMath::Vector3(.5f, -.5f, 1.f)) *
		DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(.5f, .5f, 0.f)) *
		DirectX::SimpleMath::Matrix::CreateScale(DirectX::SimpleMath::Vector3(float(size.right), float(size.bottom), 1.f));

}

void FollowCamera::Initialize()
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
}

void FollowCamera::Update(DirectX::SimpleMath::Vector3 _eye, DirectX::SimpleMath::Vector3 _target)
{
	_target.x = Clamp(_target.x, RANGE_MIN.x, RANGE_MAX.x);
	_target.z = Clamp(_target.z, RANGE_MIN.z, RANGE_MAX.z);
	_eye.x = Clamp(_eye.x, RANGE_MIN.x, RANGE_MAX.x);
	_eye.z = Clamp(_eye.z, RANGE_MIN.z, RANGE_MAX.z);

	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(_eye, _target, m_up);
	//DoShake(0.5f, 0.3f);
}

void FollowCamera::Shake(float _duration, float _magnitude)
{
	DoShake(_duration, _magnitude);
}

void FollowCamera::DoShake(float _duration, float _magnitude)
{
	DirectX::SimpleMath::Vector3 pos = EYE_VEC;
	//float elapsed = 0.0f;
	//srand((unsigned)time(0));
	//while (elapsed < _duration)
	//{
	float x = pos.x + ((rand() % 2)) * _magnitude;
	float y = pos.y + ((rand() % 2)) * _magnitude;

	m_eye = DirectX::SimpleMath::Vector3(x, y, pos.z);

	//}
}
