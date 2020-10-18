#pragma once
#include <d3d11_1.h>
#include <SimpleMath.h>

#include "GameContext.h"
#include "DeviceResources.h"

// 追尾カメラ
class FollowCamera
{
public: // 基本

	// コンストラクタ
	FollowCamera();

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
	DirectX::SimpleMath::Matrix GetViewPort()
	{
		return m_viewPort;
	}

public: // 関数

	// 初期化
	void Initialize();
	// 更新
	void Update(DirectX::SimpleMath::Vector3 _eye, DirectX::SimpleMath::Vector3 _target);

private: // サブ関数

	void Shake(float _duration, float _magnitude);

	void DoShake(float _duration, float _magnitude);

public: // 定数

	// 視点
	static const DirectX::SimpleMath::Vector3 EYE_VEC;
	// カメラ上
	static const DirectX::SimpleMath::Vector3 UP_VEC;
	// 移動制限範囲
	static const DirectX::SimpleMath::Vector3 RANGE_MIN;
	static const DirectX::SimpleMath::Vector3 RANGE_MAX;


private: // 変数

	DirectX::SimpleMath::Matrix m_view;

	// 視点
	DirectX::SimpleMath::Vector3 m_eye;
	// 注視点
	DirectX::SimpleMath::Vector3 m_target;
	DirectX::SimpleMath::Vector3 m_up;

	// ViewPort
	DirectX::SimpleMath::Matrix							m_viewPort;

};