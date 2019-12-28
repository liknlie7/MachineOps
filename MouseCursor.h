#pragma once

#include <SimpleMath.h>
#include <mouse.h>
#include <SpriteBatch.h>

#include "DeviceResources.h"
#include "FollowCamera.h"
#include "GameContext.h"
#include "Projection.h"
#include "WICTextureLoader.h" 

class MouseCursor
{
public: // 基本

	// コンストラクタ
	MouseCursor();
	// デストラクタ
	~MouseCursor() {}

public: // アクセサ

	DirectX::SimpleMath::Vector3 GetRayNear() const
	{
		return m_rayNear;
	}

	DirectX::SimpleMath::Vector3 GetRayFar() const
	{
		return m_rayFar;
	}

public: // 関数

	// 更新
	void Update();

	// 描画
	void Render();

private: // 変数

	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_reticle;

	// 位置
	DirectX::SimpleMath::Vector3							m_pos;

	// Ray
	DirectX::SimpleMath::Vector3							m_rayNear;
	DirectX::SimpleMath::Vector3							m_rayFar;

	// マウスState
	DirectX::SimpleMath::Vector3							m_state;
};

