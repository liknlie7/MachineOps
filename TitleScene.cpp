#include "pch.h"

#include "TitleScene.h"

#include "DebugFont.h"
#include "GameContext.h"
#include "GameSceneManager.h"

using namespace std;

using namespace DirectX;
using namespace DirectX::SimpleMath;

TitleScene::TitleScene()
	: GameScene()
	, m_time(0)
{
	m_spriteFont = make_unique<SpriteFont>(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"SegoeUI_18.spritefont");

	m_keyboardTracker = GameContext::Get<Keyboard::KeyboardStateTracker>();
	alpha = 1;
	color = Vector4(0, 0, 0, alpha);
	fadeFlag = true;
}


TitleScene::~TitleScene()
{
}


void TitleScene::Initialize()
{
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\BackGround.png", nullptr, m_backGroundTexture.GetAddressOf());
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\Title.png", nullptr, m_titleTexture.GetAddressOf());
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\Massage.png", nullptr, m_massageTexture.GetAddressOf());
}


void TitleScene::Update(DX::StepTimer const& _timer)
{
	auto effectMask = GameContext::Get<EffectManager>();

	float elapsedTime = float(_timer.GetElapsedSeconds());
	m_time += elapsedTime;

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
	m_keyboardTracker->Update(keyState);

	if (m_keyboardTracker->pressed.Space)
	{
		effectMask->Close();
	}
	// ‰æ–Ê‚ª•Â‚¶‚é‚Ü‚Å‚Ü‚Â
	if (effectMask->IsClose())
	{
		GameSceneManager* gameSceneManager = GameContext::Get<GameSceneManager>();
		gameSceneManager->RequestScene("Play");
	}
}


void TitleScene::Render()
{
	SpriteBatch* spriteBatch = GameContext::Get<SpriteBatch>();

	spriteBatch->Begin();
	spriteBatch->Draw(m_backGroundTexture.Get(), Vector2::Zero);
	spriteBatch->Draw(m_titleTexture.Get(), Vector2(190, 220), nullptr, Colors::White, 0.0f, Vector2::Zero, Vector2(0.8f, 0.8f));
	if (sin(m_time * 4) > 0)
	spriteBatch->Draw(m_massageTexture.Get(), Vector2(380,450), nullptr, Colors::White, 0.0f, Vector2::Zero, Vector2(0.3f, 0.3f));
	spriteBatch->End();
}


void TitleScene::Finalize()
{
	m_spriteFont.reset();
}