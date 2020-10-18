#include "pch.h"

#include <SpriteBatch.h>

#include "ResultClearScene.h"
#include "GameContext.h"
#include "ResourceManager.h"

// コンストラクタ
ResultClearScene::ResultClearScene()

{
	m_keyboardTracker = GameContext::Get<DirectX::Keyboard::KeyboardStateTracker>();
}

// 初期化
void ResultClearScene::Initialize()
{
	// テクスチャデータを受け取る
	// 背景
	m_textures[BACK_GROUND] = ResourceManager::GetInstance()->GetTexture(L"Resources\\Textures\\ResultBackGround.png");
	
	// テキスト
	m_textures[TEXT] = ResourceManager::GetInstance()->GetTexture(L"Resources\\Textures\\GameClear.png");
}

// 更新
void ResultClearScene::Update(DX::StepTimer const & _timer)
{
	_timer;

	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	m_keyboardTracker->Update(keyState);

	if (m_keyboardTracker->pressed.Space)
	{
		SceneManager::GetInstance()->RequestScene(eScene::TITLE);
	}
}

// 描画
void ResultClearScene::Render()
{
	// スプライトバッチの取得
	DirectX::SpriteBatch* spriteBatch = GameContext::Get<DirectX::SpriteBatch>();

	// テクスチャ描画
	spriteBatch->Begin();
	spriteBatch->Draw(m_textures[BACK_GROUND].Get(), DirectX::SimpleMath::Vector2::Zero, nullptr, DirectX::Colors::White, 0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(1.2f, 1.2f));
	spriteBatch->Draw(m_textures[TEXT].Get(), DirectX::SimpleMath::Vector2(290, 250), nullptr, DirectX::Colors::White, 0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(0.8f, 0.8f));
	spriteBatch->End();
}

// 後処理
void ResultClearScene::Finalize()
{

}
