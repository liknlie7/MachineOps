#pragma once

#include "GameScene.h"
#include "DeviceResources.h"

#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <Keyboard.h>
#include <CommonStates.h>
#include <WICTextureLoader.h>

#include "GameSceneManager.h"
#include "StepTimer.h"
#include "GameContext.h"
#include "EffectMask.h"
#include "Adx2Le.h"
#include "TitleSoundSeet.h"

// タイトルシーン
class TitleScene : public GameScene
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
	void Finalize() override;

private: // 変数

	// スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch>	m_spriteBatch;

	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_titleTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_backGroundTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_massageTexture;

	// キーボードトラッカー
	DirectX::Keyboard::KeyboardStateTracker*				m_keyboardTracker;

	// 経過時間
	float m_time;
};