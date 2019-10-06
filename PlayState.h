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

	// デバッグ用カメラ、床
	std::unique_ptr<DebugCamera>						m_pDebugCamera;
	std::unique_ptr<GridFloor>							m_pGridFloor;

	// Device Resources
	DX::DeviceResources*								m_pDeviceResources;
	ID3D11Device*										m_pDevice;
	ID3D11DeviceContext*								m_pDeviceContext;

	// コモンステート
	DirectX::CommonStates*								m_pState;

	// エフェクト
	std::unique_ptr<DirectX::BasicEffect>				m_pBasicEffect;

	// 射影行列
	Projection*											m_pProjection;

	// ViewPort
	DirectX::SimpleMath::Matrix							m_viewPort;

	// 追尾カメラ
	std::unique_ptr<FollowCamera>						m_pFollowCamera;

	// フロア
	std::unique_ptr<Floor>								m_pFloor;

	// プレイヤー
	std::unique_ptr<Player>								m_pPlayer;

	// 敵
	std::unique_ptr<Enemy>								m_pEnemy1[2];
	std::unique_ptr<Enemy>								m_pEnemy2[2];

	// 色
	DirectX::SimpleMath::Color							m_color;
};