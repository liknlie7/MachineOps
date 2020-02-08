#pragma once

#include <SimpleMath.h>
#include <WICTextureLoader.h>
#include <SpriteBatch.h>

#include "GameContext.h"
#include "DeviceResources.h"
#include "Projection.h"

// 警告ライン
class WarningLine
{
public: // 基本

	// コンストラクタ
	WarningLine();
	// デストラクタ
	~WarningLine() {};


private: // 定数

	// エフェクト表示時間
	static const float DISPLAY_TIME;

public: // 関数

	// 初期化
	void Initialize();

	// 更新
	void Update(float _elapsedTime);

	// 描画
	void Render();

private: // 変数

	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_texture;

	// 表示時間カウンタ
	float m_timer;

};

