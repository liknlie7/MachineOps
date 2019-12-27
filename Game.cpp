//
// Game.cpp
//

#include "pch.h"
#include "Game.h"

#include <random>

#include "DebugFont.h"
#include "GameContext.h"
#include "GameSceneManager.h"

#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"

extern void ExitGame();


using namespace DirectX;
using namespace DirectX::SimpleMath;

using namespace std;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false)
{
	m_pDeviceResources = make_unique<DX::DeviceResources>();
	m_pDeviceResources->RegisterDeviceNotify(this);
	GameContext::Register<DX::DeviceResources>(m_pDeviceResources);
}

Game::~Game()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->reset();
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
	// マウスの作成
	m_pMouse = make_unique<Mouse>();
	m_pMouse->SetWindow(window);

	// キーボードの作成
	m_pKeyboard = make_unique<Keyboard>();

	m_pDeviceResources->SetWindow(window, width, height);

	m_pDeviceResources->CreateDeviceResources();
	CreateDeviceDependentResources();

	// コモンステート作成
	m_pState = make_unique<CommonStates>(m_pDeviceResources->GetD3DDevice());
	GameContext::Register<CommonStates>(m_pState);

	// スプライトバッチの作成
	m_pSpriteBatch = std::make_unique<SpriteBatch>(m_pDeviceResources->GetD3DDeviceContext());
	GameContext::Register<SpriteBatch>(m_pSpriteBatch);

	// サウンドの作成
	m_pSound = new Sound;
	m_pSound->Initialize(window);
	GameContext::Register<Sound>(m_pSound);

	m_pDeviceResources->CreateWindowSizeDependentResources();
	CreateWindowSizeDependentResources();

	// TODO: Change the timer settings if you want something other than the default variable timestep mode.
	// e.g. for 60 FPS fixed timestep update logic, call:
	/*
	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);
	*/


	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->create(m_pDeviceResources->GetD3DDevice(), m_pDeviceResources->GetD3DDeviceContext());


	m_pGameSceneManager = make_unique<GameSceneManager>();
	m_pGameSceneManager->RegisterScene<TitleScene>("Title");
	m_pGameSceneManager->RegisterScene<PlayScene>("Play");
	m_pGameSceneManager->RegisterScene<ResultScene>("Result");
	m_pGameSceneManager->SetStartScene("Title");
	GameContext::Register<GameSceneManager>(m_pGameSceneManager);
}


#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
	m_timer.Tick([&]()
	{
		Update(m_timer);
	});

	Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
	float elapsedTime = float(timer.GetElapsedSeconds());

	// TODO: Add your game logic here.
	elapsedTime;
	
	m_pGameSceneManager->Update(timer);
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
	// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		return;
	}

	Clear();

	m_pDeviceResources->PIXBeginEvent(L"Render");
	auto context = m_pDeviceResources->GetD3DDeviceContext();

	// TODO: Add your rendering code here.
	context;
	m_pGameSceneManager->Render();

	m_pDeviceResources->PIXEndEvent();
	// Show the new frame.
	m_pDeviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
	m_pDeviceResources->PIXBeginEvent(L"Clear");

	// Clear the views.
	auto context = m_pDeviceResources->GetD3DDeviceContext();
	auto renderTarget = m_pDeviceResources->GetRenderTargetView();
	auto depthStencil = m_pDeviceResources->GetDepthStencilView();

	context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
	context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->OMSetRenderTargets(1, &renderTarget, depthStencil);

	// Set the viewport.
	auto viewport = m_pDeviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	m_pDeviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
	// TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
	// TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
	// TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
	m_timer.ResetElapsedTime();

	// TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowMoved()
{
	auto r = m_pDeviceResources->GetOutputSize();
	m_pDeviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnWindowSizeChanged(int width, int height)
{
	if (!m_pDeviceResources->WindowSizeChanged(width, height))
		return;

	CreateWindowSizeDependentResources();

	// TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
	// TODO: Change to desired default window size (note minimum size is 320x200).
	width = 1280;
	height = 720;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
	auto device = m_pDeviceResources->GetD3DDevice();

	// TODO: Initialize device dependent objects here (independent of window size).
	device;
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
	// TODO: Initialize windows-size dependent objects here.

	// ウインドウサイズからアスペクト比を算出する
	RECT size = m_pDeviceResources->GetOutputSize();
	float aspectRatio = float(size.right) / float(size.bottom);

	// 画角を設定
	float fovAngleY = XMConvertToRadians(45.0f);

	// 射影行列を作成する
	m_pProjection = std::make_unique<Projection>();
	m_pProjection->SetPerspectiveFieldOfView(
		fovAngleY,
		aspectRatio,
		0.01f,
		100.0f
	);
	GameContext::Register<Projection>(m_pProjection);
}

void Game::OnDeviceLost()
{
	// TODO: Add Direct3D resource cleanup here.
}

void Game::OnDeviceRestored()
{
	CreateDeviceDependentResources();

	CreateWindowSizeDependentResources();
}
#pragma endregion