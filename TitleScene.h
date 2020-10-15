#pragma once

#include <SpriteBatch.h>
#include <Keyboard.h>
#include <SimpleMath.h>

#include "SceneManager.h"
#include "StepTimer.h"
#include "Adx2Le.h"

class IScene;

// タイトルシーン
class TitleScene : public IScene
{

public: // 基本

	// コンストラクタ
	TitleScene();

	// デストラクタ
	virtual ~TitleScene();

public: // 関数

	// 初期化
	void Initialize() override;
	
	// 更新
	void Update(DX::StepTimer const& _timer) override;
	
	// 描画
	void Render() override;
	
	// 後処理
	void Finalize() override {};

private: // 定数

	// テクスチャ用
	enum Texture
	{
		TITLE = 1,		// タイトル名
		BACK_GROUND,	// 背景
		TEXT,			// テキスト

		ALL,
	};

	// タイトル位置
	static const DirectX::SimpleMath::Vector2 TITLE_POSITION;

	// タイトル拡大率
	static const DirectX::SimpleMath::Vector2 TITLE_SCALE;

	// テキスト位置
	static const DirectX::SimpleMath::Vector2 TEXT_POSITION;

	// テキスト拡大率
	static const DirectX::SimpleMath::Vector2 TEXT_SCALE;

private: // 変数

	// サウンド
	std::weak_ptr<Adx2Le>									m_pSound;

	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_pTextures[Texture::ALL];

	// キーボードトラッカー
	DirectX::Keyboard::KeyboardStateTracker*				m_pKeyboardTracker;

	// 経過時間
	float m_time;
};