#include "pch.h"

#include "ResultScene.h"

#include "DebugFont.h"
#include "GameContext.h"
#include "GameSceneManager.h"

using namespace std;

using namespace DirectX;

ResultScene::ResultScene()
	: GameScene()
{
	m_spriteBatch = std::make_unique<SpriteBatch>(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext());
	m_spriteFont = make_unique<SpriteFont>(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"SegoeUI_18.spritefont");
}


ResultScene::~ResultScene()
{

}


void ResultScene::Initialize()
{

}


void ResultScene::Update(DX::StepTimer const& _timer)
{
	Keyboard::State keyState = Keyboard::Get().GetState();

	if (keyState.IsKeyDown(Keyboard::Space))
	{
		GameSceneManager* gameSceneManager = GameContext::Get<GameSceneManager>();
		gameSceneManager->RequestScene("Title");
	}

}


void ResultScene::Render()
{
	m_spriteBatch->Begin(SpriteSortMode_Deferred, GameContext::Get<CommonStates>()->NonPremultiplied());
	m_spriteFont->DrawString(m_spriteBatch.get(), "Coming soon...", SimpleMath::Vector2(550, 520), Colors::Black, 0, SimpleMath::Vector2(0, 0), 1.5f);
	m_spriteBatch->End();
}


void ResultScene::Finalize()
{
	m_spriteBatch.reset();
	m_spriteFont.reset();
}