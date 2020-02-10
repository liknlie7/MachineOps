#pragma once

#include <SimpleMath.h>
#include <WICTextureLoader.h>
#include <SpriteBatch.h>

#include "GameContext.h"

// 警告メッセージ
class WarningMessage
{
public: // 基本

	// コンストラクタ
	WarningMessage();
	// デストラクタ
	~WarningMessage() {};

private: // 定数

	// 表示時間
	static const float DISPLAY_TIME;

	// テクスチャ回転率
	static const float ROTATION;

	// テクスチャ拡大率
	static const DirectX::SimpleMath::Vector2 MAGNIFICATION;

	// フェードスピード
	static const float FADE_SPEED;

public: // 関数

	// 初期化
	void Initialize();

	// 更新
	void Update(float _elapsedTime);

	// 描画
	void Render(ID3D11ShaderResourceView* _texture, DirectX::SimpleMath::Vector2 _pos);

private: // 変数

	// 表示時間カウンタ
	float m_timer;

	// 透明度
	float m_alpha;

	// フェードタイプ（falseならアウト）
	bool m_fadeType;

};

