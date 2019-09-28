#pragma once

#include "SimpleMath.h"
#include "Mouse.h"


class DebugCamera
{
public:

	// カメラの距離
	static const float DEFAULT_CAMERA_DISTANCE;

public:

	DebugCamera();
	~DebugCamera();

public:

	void update();

public:

	// ビュー行列取得
	DirectX::SimpleMath::Matrix getViewMatrix()
	{
		return m_view;
	}

	// 位置取得
	DirectX::SimpleMath::Vector3 getEyePosition()
	{
		return m_eye;
	}

	// 注視点取得
	DirectX::SimpleMath::Vector3 getTargetPosition()
	{
		return m_target;
	}

private:

	void motion(int x, int y);

private:

	// 横回転
	float m_yAngle;
	// 縦回転
	float m_xAngle;

	// 前回のマウス座標
	int m_prevX, m_prevY;

	// 生成されたビュー行列
	DirectX::SimpleMath::Matrix m_view;

	// スクロールフォイール値
	int m_scrollWheelValue;

	// 視点
	DirectX::SimpleMath::Vector3 m_eye;

	// 注視点
	DirectX::SimpleMath::Vector3 m_target;

	// マウストラッカー
	DirectX::Mouse::ButtonStateTracker m_tracker;
};