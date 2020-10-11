#pragma once

#include <SpriteBatch.h>
#include <Keyboard.h>
#include <CommonStates.h>
#include <WICTextureLoader.h>
#include <SimpleMath.h>
#include "StepTimer.h"

#include "GameScene.h"
#include "DeviceResources.h"
#include "SceneManager.h"

class IScene;

// クリアシーン
class ResultClearScene : public IScene
{
public: // 基本

	// コンストラクタ
	ResultClearScene();

	// デストラクタ
	virtual ~ResultClearScene();

public: // 関数

	// 初期化
	eScene Initialize() override;
	
	// 更新
	eScene Update(DX::StepTimer const& _timer) override;
	
	//描画
	eScene Render() override;
	
	// 後処理
	eScene Finalize() override;

private: // 変数

	// キーボードトラッカー
	DirectX::Keyboard::KeyboardStateTracker*	m_keyboardTracker;

	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_backGroundTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_clearTexture;
};

