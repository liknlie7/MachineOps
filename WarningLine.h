#pragma once

#include <SimpleMath.h>
#include <WICTextureLoader.h>
#include <SpriteBatch.h>

// 警告ライン
class WarningLine
{
public: // 基本

	// コンストラクタ
	WarningLine();
	
	// デストラクタ
	~WarningLine() {};

public: // 関数

	// 初期化
	void Initialize(DirectX::SimpleMath::Vector2 _pos, bool _dir);

	// 更新
	void Update(float _elapsedTime);

	// 描画
	void Render(ID3D11ShaderResourceView* _texture);

private: // 定数

	// 表示時間
	static const float DISPLAY_TIME;

	// テクスチャ回転率
	static const float ROTATION;

	// テクスチャ拡大率
	static const DirectX::SimpleMath::Vector2 MAGNIFICATION;

	// 速度
	static const float SPEED;

private: // 変数

	// 表示時間カウンタ
	float m_timer;

	// 座標
	DirectX::SimpleMath::Vector2 m_pos;

	// 向き（左方向ならfalse
	bool m_dir;
};

