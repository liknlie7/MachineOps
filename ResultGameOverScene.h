#pragma once
#include "GameScene.h"
#include "DeviceResources.h"

#include <SpriteBatch.h>
#include <Keyboard.h>
#include <CommonStates.h>
#include <WICTextureLoader.h>
#include <SimpleMath.h>
#include "StepTimer.h"

// ゲームオーバーシーン
class ResultGameOverScene : public GameScene
{
public: // 基本

	// コンストラクタ
	ResultGameOverScene();
	// デストラクタ
	virtual ~ResultGameOverScene();

public: // 関数

	// 初期化
	void Initialize() override;
	// 更新
	void Update(DX::StepTimer const& _timer) override;
	//描画
	void Render() override;
	// 後処理
	void Finalize() override;

private: // 変数

	// キーボードトラッカー
	DirectX::Keyboard::KeyboardStateTracker*	m_keyboardTracker;

	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_backGroundTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_gameOverTexture;

};

