#pragma once

#include <memory>
#include <CommonStates.h>
#include <SpriteBatch.h>
#include <SimpleMath.h>
#include <Effects.h>
#include <Keyboard.h>

#include "DeviceResources.h"
#include "GameContext.h"
#include "GameState.h"
#include "Projection.h"
#include "StepTimer.h"
#include "Keyboard.h"
#include "GameStateManager.h"

#include "DebugFont.h"
#include "DebugCamera.h"
#include "GridFloor.h"
#include "FollowCamera.h"
#include "Floor.h"
#include "Player.h"
#include "Enemy.h"
#include "Collision.h"

class PlayState : public GameState
{
public:

	PlayState();
	virtual ~PlayState();

public:

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Finalize() override;

private:

	// �f�o�b�O�p�J�����A��
	std::unique_ptr<DebugCamera>						m_pDebugCamera;
	std::unique_ptr<GridFloor>							m_pGridFloor;

	// Device Resources
	DX::DeviceResources*								m_pDeviceResources;
	ID3D11Device*										m_pDevice;
	ID3D11DeviceContext*								m_pDeviceContext;

	// �R�����X�e�[�g
	DirectX::CommonStates*								m_pState;

	// �G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect>				m_pBasicEffect;

	// �ˉe�s��
	Projection*											m_pProjection;

	// ViewPort
	DirectX::SimpleMath::Matrix							m_viewPort;

	// �ǔ��J����
	std::unique_ptr<FollowCamera>						m_pFollowCamera;

	// �t���A
	std::unique_ptr<Floor>								m_pFloor;

	// �v���C���[
	std::unique_ptr<Player>								m_pPlayer;

	// �G
	std::unique_ptr<Enemy>								m_pEnemy1[2];
	std::unique_ptr<Enemy>								m_pEnemy2[2];

	// �F
	DirectX::SimpleMath::Color							m_color;
};