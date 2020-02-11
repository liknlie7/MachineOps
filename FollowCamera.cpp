#include "pch.h"

#include "FollowCamera.h"

#include <random>
#include <time.h>
using namespace DirectX;
using namespace DirectX::SimpleMath;

// 真上
const Vector3 FollowCamera::EYE_VEC = Vector3(0.0f, 30.0f, 0.0f);
const Vector3 FollowCamera::UP_VEC = Vector3(0.0f, 0.0f, -1.0f);




FollowCamera::FollowCamera()
{
	m_eye = EYE_VEC;
	m_target = Vector3(0.0f, 0.0f, 0.0f);
	m_up = UP_VEC;

	// ビューポートの作成
	RECT size = GameContext::Get<DX::DeviceResources>()->GetOutputSize();
	m_viewPort =
		Matrix::CreateScale(Vector3(.5f, -.5f, 1.f)) *
		Matrix::CreateTranslation(Vector3(.5f, .5f, 0.f)) *
		Matrix::CreateScale(Vector3(float(size.right), float(size.bottom), 1.f));

}

void FollowCamera::Initialize()
{
	m_view = Matrix::CreateLookAt(m_eye, m_target, m_up);
}

void FollowCamera::Update(Vector3 _eye, Vector3 _target)
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(_eye, _target, m_up);
	//DoShake(0.5f, 0.3f);
}

void FollowCamera::Shake(float _duration, float _magnitude)
{
	DoShake(_duration, _magnitude);
}

void FollowCamera::DoShake(float _duration, float _magnitude)
{
	Vector3 pos = EYE_VEC;
	//float elapsed = 0.0f;
	//srand((unsigned)time(0));
	//while (elapsed < _duration)
	//{
		float x = pos.x + ((rand() % 2)) * _magnitude;
		float y = pos.y + ((rand() % 2)) * _magnitude;

		m_eye = Vector3(x, y, pos.z);

	//}
}
