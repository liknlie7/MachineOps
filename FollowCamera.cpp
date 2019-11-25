#include "pch.h"

#include "FollowCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//const Vector3 FollowCamera::EYE_VEC = Vector3(0.0f, 15.0f, 18.0f);
const Vector3 FollowCamera::EYE_VEC = Vector3(0.0f, 50.0f, 0.0f);
//const Vector3 FollowCamera::UP_VEC = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 FollowCamera::UP_VEC = Vector3(0.0f, 0.0f, -1.0f);



FollowCamera::FollowCamera()
{
	m_eye = EYE_VEC;
	m_target = Vector3(0.0f, 0.0f, 0.0f);
	m_up = UP_VEC;
}

void FollowCamera::Initialize()
{
	m_view = Matrix::CreateLookAt(m_eye, m_target, m_up);
}

void FollowCamera::Update(Vector3 _eye, Vector3 _target)
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(_eye, _target, m_up);
}