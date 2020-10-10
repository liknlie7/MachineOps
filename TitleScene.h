#pragma once

#include "GameScene.h"
#include "DeviceResources.h"

#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <Keyboard.h>
#include <CommonStates.h>
#include <WICTextureLoader.h>

#include "GameSceneManager.h"
#include "SceneManager.h"
#include "StepTimer.h"
#include "GameContext.h"
#include "EffectMask.h"
#include "Adx2Le.h"
#include "TitleSoundSeet.h"
#include "ResourceManager.h"

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
	eScene Initialize() override;
	// 更新
	eScene Update(DX::StepTimer const& _timer) override;
	// 描画
	eScene Render() override;
	// 後処理
	eScene Finalize() override;

private: // 変数

	// サウンド
	std::weak_ptr<Adx2Le>									m_pSound;

	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_titleTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_backGroundTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_massageTexture;

	// キーボードトラッカー
	DirectX::Keyboard::KeyboardStateTracker*				m_keyboardTracker;

	// 経過時間
	float m_time;

	// サウンドフェード用
	bool m_volumeFadeFlag;
	float m_volume;
};