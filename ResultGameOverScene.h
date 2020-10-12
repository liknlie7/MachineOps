#pragma once

#include <SpriteBatch.h>
#include <Keyboard.h>
#include <CommonStates.h>
#include <WICTextureLoader.h>
#include <SimpleMath.h>

#include "DeviceResources.h"
#include "StepTimer.h"
#include "SceneManager.h"
#include "ResourceManager.h"

class IScene;

// ゲームオーバーシーン
class ResultGameOverScene : public IScene
{
public: // 基本

	// コンストラクタ
	ResultGameOverScene();

	// デストラクタ
	virtual ~ResultGameOverScene();

public: // 関数

	// 初期化
	eScene Initialize() override;

	// 更新
	eScene Update(DX::StepTimer const& _timer) override;
	
	//描画
	eScene Render() override;
	
	// 後処理
	eScene Finalize() override;

private: // 定数

	// テクスチャ
	enum Texture
	{
		BACK_GROUND = 1,// 背景
		TEXT,			// テキスト

		ALL,			// 全てのテクスチャ
	};

private: // 変数

	// キーボードトラッカー
	DirectX::Keyboard::KeyboardStateTracker*	m_keyboardTracker;

	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_textures[Texture::ALL];

};

