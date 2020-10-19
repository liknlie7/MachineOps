#include "../../pch.h"

#include "../Common/Utilities.h"
#include "../Common/GameContext.h"
#include "../Common/DeviceResources.h"
#include "FollowCamera.h"

// 視点
const DirectX::SimpleMath::Vector3 FollowCamera::EYE_VEC = DirectX::SimpleMath::Vector3(0.0f, 30.0f, 0.0f);

// カメラの向き
const DirectX::SimpleMath::Vector3 FollowCamera::UP_VEC = DirectX::SimpleMath::Vector3(0.0f, 0.0f, -1.0f);

// 移動制限範囲
const DirectX::SimpleMath::Vector3 FollowCamera::RANGE_MIN = DirectX::SimpleMath::Vector3(-5.0f, 0.0f, -9.0f);
const DirectX::SimpleMath::Vector3 FollowCamera::RANGE_MAX = DirectX::SimpleMath::Vector3(5.0f, 0.0f, 10.0f);

// コンストラクタ
FollowCamera::FollowCamera()
{
	// 視点設定
	m_eye = EYE_VEC;

	// 注視点設定
	m_target = DirectX::SimpleMath::Vector3::Zero;

	// カメラ上面設定
	m_up = UP_VEC;

	// ビューポートの作成
	RECT size = GameContext::Get<DX::DeviceResources>()->GetOutputSize();
	m_viewPort =
		DirectX::SimpleMath::Matrix::CreateScale(DirectX::SimpleMath::Vector3(0.5f, -0.5f, 1.0f)) *
		DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(0.5f, 0.5f, 0.0f)) *
		DirectX::SimpleMath::Matrix::CreateScale(DirectX::SimpleMath::Vector3(float(size.right), float(size.bottom), 1.0f));
}

// 初期化
void FollowCamera::Initialize()
{
	// 視界の作成
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
}

// 更新
void FollowCamera::Update(DirectX::SimpleMath::Vector3 _eye, DirectX::SimpleMath::Vector3 _target)
{
	// ステージ外に行かないように範囲を制御
	_target.x = Clamp(_target.x, RANGE_MIN.x, RANGE_MAX.x);
	_target.z = Clamp(_target.z, RANGE_MIN.z, RANGE_MAX.z);
	_eye.x = Clamp(_eye.x, RANGE_MIN.x, RANGE_MAX.x);
	_eye.z = Clamp(_eye.z, RANGE_MIN.z, RANGE_MAX.z);

	// 視界の更新
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(_eye, _target, m_up);
}