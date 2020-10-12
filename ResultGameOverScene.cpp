#include "pch.h"
#include "ResultGameOverScene.h"

#include "GameContext.h"
//#include "GameSceneManager.h"

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
	// テクスチャデータを受け取る
	m_textures[BACK_GROUND] = ResourceManager::GetInstance().GetTexture(L"Resources\\Textures\\ResultBackGround.png");
	m_textures[TEXT] = ResourceManager::GetInstance().GetTexture(L"Resources\\Textures\\GameOver.png");

	return eScene::RESULT_GAMEOVER;
}

// 更新
eScene ResultGameOverScene::Update(DX::StepTimer const & _timer)
{
	_timer;
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	m_keyboardTracker->Update(keyState);

	if (m_keyboardTracker->pressed.Space)
	{
		//GameSceneManager* gameSceneManager = GameContext::Get<GameSceneManager>();
		//gameSceneManager->RequestScene("Title");
	}

	return eScene::RESULT_GAMEOVER;
}

// 描画
eScene ResultGameOverScene::Render()
{
	// スプライトバッチの取得
	DirectX::SpriteBatch* spriteBatch = GameContext::Get<DirectX::SpriteBatch>();

	// テクスチャ描画
	spriteBatch->Begin();
	spriteBatch->Draw(m_textures[BACK_GROUND].Get(), DirectX::SimpleMath::Vector2::Zero, nullptr, DirectX::Colors::White, 0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(1.2f, 1.2f));
	spriteBatch->Draw(m_textures[TEXT].Get(), DirectX::SimpleMath::Vector2(330, 250), nullptr, DirectX::Colors::White, 0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(0.8f, 0.8f));
	spriteBatch->End();

	return eScene::RESULT_GAMEOVER;
}

// 後処理
eScene ResultGameOverScene::Finalize()
{
	return eScene::RESULT_GAMEOVER;
}
