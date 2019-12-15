#include "pch.h"

#include "ResultState.h"

#include "DebugFont.h"
#include "GameContext.h"
#include "GameStateManager.h"

using namespace std;

using namespace DirectX;

ResultState::ResultState()
	: GameState()
{
	m_spriteBatch = std::make_unique<SpriteBatch>(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext());
	m_spriteFont = make_unique<SpriteFont>(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"SegoeUI_18.spritefont");
}


ResultState::~ResultState()
{

}


void ResultState::Initialize()
{

}


void ResultState::Update()
{
	Keyboard::State keyState = Keyboard::Get().GetState();

	if (keyState.IsKeyDown(Keyboard::Space))
	{
		GameStateManager* gameStateManager = GameContext::Get<GameStateManager>();
		gameStateManager->RequestState("Title");
	}

}


void ResultState::Render()
{
	m_spriteBatch->Begin(SpriteSortMode_Deferred, GameContext::Get<CommonStates>()->NonPremultiplied());
	m_spriteFont->DrawString(m_spriteBatch.get(), "Coming soon...", SimpleMath::Vector2(550, 520), Colors::Black, 0, SimpleMath::Vector2(0, 0), 1.5f);
	m_spriteBatch->End();
}


void ResultState::Finalize()
{
	m_spriteBatch.reset();
	m_spriteFont.reset();
}