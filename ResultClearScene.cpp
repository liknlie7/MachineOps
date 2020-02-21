#include "pch.h"
#include "ResultClearScene.h"

#include "GameContext.h"
#include "GameSceneManager.h"

// コンストラクタ
ResultClearScene::ResultClearScene()
	: GameScene()

{
	m_keyboardTracker = GameContext::Get<DirectX::Keyboard::KeyboardStateTracker>();
}

// デストラクタ
ResultClearScene::~ResultClearScene()
{
}

// 初期化
void ResultClearScene::Initialize()
{
	// テクスチャ読み込み
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\ResultBackGround.png", nullptr, m_backGroundTexture.GetAddressOf());
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\GameClear.png", nullptr, m_clearTexture.GetAddressOf());
}

// 更新
void ResultClearScene::Update(DX::StepTimer const & _timer)
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
void ResultClearScene::Render()
{
	// スプライトバッチの取得
	DirectX::SpriteBatch* spriteBatch = GameContext::Get<DirectX::SpriteBatch>();

	// テクスチャ描画
	spriteBatch->Begin();
	spriteBatch->Draw(m_backGroundTexture.Get(), DirectX::SimpleMath::Vector2::Zero, nullptr, DirectX::Colors::White, 0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(1.2f, 1.2f));
	spriteBatch->Draw(m_clearTexture.Get(), DirectX::SimpleMath::Vector2(290, 250), nullptr, DirectX::Colors::White, 0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(0.8f, 0.8f));
	spriteBatch->End();
}

// 後処理
void ResultClearScene::Finalize()
{
}
