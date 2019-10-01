//
// Game.h
//

#pragma once

#include <CommonStates.h>
#include <SpriteBatch.h>
#include <SimpleMath.h>
#include <unordered_map>
#include "DeviceResources.h"
#include "Projection.h"
#include "StepTimer.h"
#include "Mouse.h"
#include "Keyboard.h"


class GameStateManager;


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game : public DX::IDeviceNotify
{
public:
	static LPCWSTR WINDOW_NAME;

public:

	Game() noexcept(false);
	~Game();

	// Initialization and management
	void Initialize(HWND window, int width, int height);

	// Basic game loop
	void Tick();

	// IDeviceNotify
	virtual void OnDeviceLost() override;
	virtual void OnDeviceRestored() override;

	// Messages
	void OnActivated();
	void OnDeactivated();
	void OnSuspending();
	void OnResuming();
	void OnWindowMoved();
	void OnWindowSizeChanged(int width, int height);

	// Properties
	void GetDefaultSize(int& width, int& height) const;

private:

	void Update(DX::StepTimer const& timer);
	void Render();

	void Clear();

	void CreateDeviceDependentResources();
	void CreateWindowSizeDependentResources();

	// Device resources.
	std::unique_ptr<DX::DeviceResources>    m_deviceResources;

	// Rendering loop timer.
	DX::StepTimer                           m_timer;

	// �ˉe�s��
	std::unique_ptr<Projection>             m_projection;

	// �}�E�X
	std::unique_ptr<DirectX::Mouse>			m_mouse;

	// �L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard>      m_keyboard;

	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates>	m_state;

	// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch>   m_spriteBatch;

	// �R�����X�e�[�g
	std::unique_ptr<GameStateManager>       m_gameStateManager;
};