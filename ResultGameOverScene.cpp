#include "pch.h"
#include "ResultGameOverScene.h"

#include "GameContext.h"
#include "GameSceneManager.h"

// コンストラクタ
ResultGameOverScene::ResultGameOverScene()
{
	m_keyboardTracker = GameContext::Get<DirectX::Keyboard::KeyboardStateTracker>();
}

// デストラクタ
ResultGameOverScene::~ResultGameOverScene()
{
}

// 初期化
eScene ResultGameOverScene::Initialize()
{
	// テクスチャ読み込み
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\ResultBackGround.png", nullptr, m_backGroundTexture.GetAddressOf());
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\GameOver.png", nullptr, m_gameOverTexture.GetAddressOf());
}

// 更新
eScene ResultGameOverScene::Update(DX::StepTimer const & _timer)
{
	_timer;
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	m_keyboardTracker->Update(keyState);

	if (m_keyboardTracker->pressed.Space)
	{
		GameSceneManager* gameSceneManager = GameContext::Get<GameSceneManager>();
		gameSceneManager->RequestScene("Title");
	}
}

// 描画
eScene ResultGameOverScene::Render()
{
	// スプライトバッチの取得
	DirectX::SpriteBatch* spriteBatch = GameContext::Get<DirectX::SpriteBatch>();

	// テクスチャ描画
	spriteBatch->Begin();
	spriteBatch->Draw(m_backGroundTexture.Get(), DirectX::SimpleMath::Vector2::Zero, nullptr, DirectX::Colors::White, 0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(1.2f, 1.2f));
	spriteBatch->Draw(m_gameOverTexture.Get(), DirectX::SimpleMath::Vector2(330, 250), nullptr, DirectX::Colors::White, 0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(0.8f, 0.8f));
	spriteBatch->End();
}

// 後処理
eScene ResultGameOverScene::Finalize()
{
}
