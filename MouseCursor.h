#pragma once

#include <SimpleMath.h>
#include <mouse.h>
#include <SpriteBatch.h>

#include "DeviceResources.h"
#include "FollowCamera.h"
#include "GameContext.h"
#include "Projection.h"
#include "WICTextureLoader.h" 
#include "GameObject.h"

class MouseCursor : public GameObject
{
public: // 基本

	// コンストラクタ
	MouseCursor(const std::string& _tag);
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
	void Update() override;

	// 描画
	void Render(const DirectX::SimpleMath::Matrix& _view) override;

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

