#pragma once

#include <Keyboard.h>
#include <WICTextureLoader.h>

#include "../Common/StepTimer.h"
#include "../Manager/Scenemanager.h"

class IScene;

// クリアシーン
class ResultClearScene : public IScene
{
public: // 基本

	// コンストラクタ
	ResultClearScene();

	// デストラクタ
	virtual ~ResultClearScene() {};

public: // 関数

	// 初期化
	void Initialize() override;
	
	// 更新
	void Update(DX::StepTimer const& _timer) override;
	
	//描画
	void Render() override;
	
	// 後処理
	void Finalize() override {};
	
private: // 定数

	// テクスチャ
	enum Texture
	{
		BACK_GROUND = 1,	// 背景
		TEXT,				// テキスト

		ALL,				// 全てのテクスチャ
	};

private: // 変数

	// キーボードトラッカー
	DirectX::Keyboard::KeyboardStateTracker*	m_keyboardTracker;

	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_textures[Texture::ALL];
};

