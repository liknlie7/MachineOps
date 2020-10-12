//
// Game.cpp
//

#include "pch.h"
#include "Game.h"

#include <random>

#include "DebugFont.h"
#include "GameContext.h"
#include "EffectMask.h"

#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultClearScene.h"
#include "ResultGameOverScene.h"

extern void ExitGame();

// TODO:Update�̈���elapsedTime�ɒu������
Game::Game() noexcept(false)
{
	m_pDeviceResources = std::make_unique<DX::DeviceResources>();
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
	// �}�E�X�̍쐬
	m_pMouse = std::make_unique<DirectX::Mouse>();
	m_pMouse->SetWindow(window);

	// �L�[�{�[�h�̍쐬
	m_pKeyboard = std::make_unique<DirectX::Keyboard>();
	m_pKeyboardTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	GameContext::Register<DirectX::Keyboard::KeyboardStateTracker>(m_pKeyboardTracker);

	m_pDeviceResources->SetWindow(window, width, height);

	m_pDeviceResources->CreateDeviceResources();
	CreateDeviceDependentResources();

	// �R�����X�e�[�g�쐬
	m_pState = std::make_unique<DirectX::CommonStates>(m_pDeviceResources->GetD3DDevice());
	GameContext::Register<DirectX::CommonStates>(m_pState);

	// �X�v���C�g�o�b�`�̍쐬
	m_pSpriteBatch = std::make_unique<DirectX::SpriteBatch>(m_pDeviceResources->GetD3DDeviceContext());
	GameContext::Register<DirectX::SpriteBatch>(m_pSpriteBatch);

	// �G�t�F�N�g�i�}�X�N�j�̍쐬
	m_effectMask = std::make_unique<EffectMask>();
	m_effectMask->Initialize(1.0f);
	GameContext::Register<EffectMask>(m_effectMask);

	// �}�E�X�J�[�\����\��
	ShowCursor(false);

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


	m_pSceneManager = std::make_unique<SceneManager>();
	m_pSceneManager->SetStartScene(eScene::TITLE);
	//m_pGameSceneManager = std::make_unique<GameSceneManager>();
	//m_pGameSceneManager->RegisterScene<TitleScene>("Title");
	//m_pGameSceneManager->RegisterScene<PlayScene>("Play");
	//m_pGameSceneManager->RegisterScene<ResultClearScene>("ResultClear");
	//m_pGameSceneManager->RegisterScene<ResultGameOverScene>("ResultGameOver");
	//
	//m_pGameSceneManager->SetStartScene("Title");
	//GameContext::Register<GameSceneManager>(m_pGameSceneManager);
	

	//m_pCollisionManager = std::make_unique<CollisionManager>();

	//m_pCollisionManager->AllowCollision("Player", "Enemy");
	//m_pCollisionManager->AllowCollision("Player", "EnemyBullet");	//m_pCollisionManager->AllowCollision("PlayerBullet", "Enemy");	//m_pCollisionManager->AllowCollision("Enemy", "Enemy");	//m_pCollisionManager->AllowCollision("Mouse", "Floor");	//m_pCollisionManager->AllowCollision("Player", "Wall");
	//GameContext::Register<CollisionManager>(m_pCollisionManager);

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

	// �V�[���̍X�V
	//m_pGameSceneManager->Update(timer);
	m_pSceneManager->Update(timer);

	// �}�X�N�̍X�V
	m_effectMask->Update(elapsedTime);

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
	//m_pGameSceneManager->Render();
	m_pSceneManager->Render();

	// �}�X�N
	m_effectMask->Render();

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

	context->ClearRenderTargetView(renderTarget, DirectX::Colors::CornflowerBlue);
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

	// �E�C���h�E�T�C�Y����A�X�y�N�g����Z�o����
	RECT size = m_pDeviceResources->GetOutputSize();
	float aspectRatio = float(size.right) / float(size.bottom);

	// ��p��ݒ�
	float fovAngleY = DirectX::XMConvertToRadians(45.0f);

	// �ˉe�s����쐬����
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