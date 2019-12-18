#include "pch.h"

#include "TitleState.h"

#include "DebugFont.h"
#include "GameContext.h"
#include "GameStateManager.h"

using namespace std;

using namespace DirectX;
using namespace DirectX::SimpleMath;

TitleState::TitleState()
	: GameState()
{
	m_spriteBatch = std::make_unique<SpriteBatch>(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext());
	m_spriteFont = make_unique<SpriteFont>(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"SegoeUI_18.spritefont");

	alpha = 1;
	color = Vector4(0, 0, 0, alpha);
	fadeFlag = true;
}


TitleState::~TitleState()
{
}


void TitleState::Initialize()
{

}


void TitleState::Update(DX::StepTimer const& timer)
{
	if (alpha >= 1)
		fadeFlag = true;

	if (alpha <= 0)
		fadeFlag = false;

	if (fadeFlag)
		alpha -= 0.01f;
	else
		alpha += 0.01f;

	color = Vector4(0, 0, 0, alpha);


	Keyboard::State keyState = Keyboard::Get().GetState();

	if (keyState.IsKeyDown(Keyboard::Space))
	{
		GameStateManager* gameStateManager = GameContext::Get<GameStateManager>();
		gameStateManager->RequestState("Play");
	}
}


void TitleState::Render()
{
	m_spriteBatch->Begin(SpriteSortMode_Deferred, GameContext::Get<CommonStates>()->NonPremultiplied());
	m_spriteFont->DrawString(m_spriteBatch.get(), "Machine Ops", SimpleMath::Vector2(260, 240), Colors::Black, 0, SimpleMath::Vector2(0, 0), 2);
	m_spriteFont->DrawString(m_spriteBatch.get(), "Press SPACE key to start", SimpleMath::Vector2(270, 400), color, 0, SimpleMath::Vector2(0, 0));
	m_spriteBatch->End();
}


void TitleState::Finalize()
{
	m_spriteBatch.reset();
	m_spriteFont.reset();
}