//
// Game.h
//

#pragma once

#include <CommonStates.h>
#include <SpriteBatch.h>
#include <mouse.h>
#include <Keyboard.h>

#include "Game/Common/DeviceResources.h"
#include "Game/Common/Projection.h"
#include "Game/Common/StepTimer.h"
#include "Game/Manager/SceneManager.h"
#include "Game/Effects/EffectMask.h"

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
	std::unique_ptr<DX::DeviceResources>    m_pDeviceResources;

	// Rendering loop timer.
	DX::StepTimer                           m_timer;

	// �ˉe�s��
	std::unique_ptr<Projection>             m_pProjection;

	// �}�E�X
	std::unique_ptr<DirectX::Mouse>			m_pMouse;

	// �L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard>      m_pKeyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_pKeyboardTracker;

	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates>	m_pState;

	// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch>   m_pSpriteBatch;

	// �V�[���Ǘ��p
	SceneManager*							m_pSceneManager;

	// �G�t�F�N�g�}�X�N
	std::unique_ptr<EffectMask>				m_pEffectMask;

};
