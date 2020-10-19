#pragma once

#include <SimpleMath.h>

// 追尾カメラ
class FollowCamera
{
public: // 基本

	// コンストラクタ
	FollowCamera();

public: // 関数

	// 初期化
	void Initialize();

	// 更新
	void Update(DirectX::SimpleMath::Vector3 _eye, DirectX::SimpleMath::Vector3 _target);

public: // アクセサ

	// ビュー行列取得
	DirectX::SimpleMath::Matrix GetViewMatrix() const
	{
		return m_view;
	}

	// 注視点の設定
	void SetTargetPosition(const DirectX::SimpleMath::Vector3& target)
	{
		m_target = target;
	}

	// 視点の設定
	void SetEyePosition(const DirectX::SimpleMath::Vector3& eye)
	{
		m_eye = eye;
	}

	// ViewPortの取得
	DirectX::SimpleMath::Matrix GetViewPort() const
	{
		return m_viewPort;
	}

public: // 定数

	// 視点
	static const DirectX::SimpleMath::Vector3 EYE_VEC;

	// カメラ上面
	static const DirectX::SimpleMath::Vector3 UP_VEC;

	// 移動制限範囲
	static const DirectX::SimpleMath::Vector3 RANGE_MIN;
	static const DirectX::SimpleMath::Vector3 RANGE_MAX;

private: // 変数

	// 視界
	DirectX::SimpleMath::Matrix		m_view;

	// 視点
	DirectX::SimpleMath::Vector3	m_eye;

	// 注視点
	DirectX::SimpleMath::Vector3	m_target;

	// カメラの上面
	DirectX::SimpleMath::Vector3	m_up;

	// ViewPort
	DirectX::SimpleMath::Matrix		m_viewPort;
};