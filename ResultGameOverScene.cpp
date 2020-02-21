#include "pch.h"
#include "ResultGameOverScene.h"

#include "GameContext.h"
#include "GameSceneManager.h"

using namespace std;

using namespace DirectX;

// コンストラクタ
ResultGameOverScene::ResultGameOverScene()
	: GameScene()
{
	m_keyboardTracker = GameContext::Get<Keyboard::KeyboardStateTracker>();
}

// デストラクタ
ResultGameOverScene::~ResultGameOverScene()
{
}

// 初期化
void ResultGameOverScene::Initialize()
{
	// テクスチャ読み込み
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\ResultBackGround.png", nullptr, m_backGroundTexture.GetAddressOf());
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\GameOver.png", nullptr, m_gameOverTexture.GetAddressOf());
}

// 更新
void ResultGameOverScene::Update(DX::StepTimer const & _timer)
{
	Keyboard::State keyState = Keyboard::Get().GetState();
	m_keyboardTracker->Update(keyState);

	if (m_keyboardTracker->pressed.Space)
	{
		GameSceneManager* gameSceneManager = GameContext::Get<GameSceneManager>();
		gameSceneManager->RequestScene("Title");
	}
}

// 描画
void ResultGameOverScene::Render()
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
void ResultGameOverScene::Finalize()
{
}
