#pragma once

#include <SimpleMath.h>
#include <SpriteBatch.h>

#include "WICTextureLoader.h" 

// 照準クラス
class Reticle
{
public: // 基本

	// コンストラクタ
	Reticle();

	// デストラクタ
	~Reticle() {}

public: // 関数

	// 更新
	void Update();

	// 描画
	void Render();

public: // アクセサ

	// Rayの始点取得
	DirectX::SimpleMath::Vector3 GetRayNear() const
	{
		return m_rayNear;
	}

	// Rayの終点取得
	DirectX::SimpleMath::Vector3 GetRayFar() const
	{
		return m_rayFar;
	}

private: // 定数

	// 照準大きさ
	static const DirectX::SimpleMath::Vector2 RETICLE_SCALE;

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