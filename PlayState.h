#pragma once

#include <memory>
#include <CommonStates.h>
#include <SpriteBatch.h>
#include <SimpleMath.h>
#include <Effects.h>
#include <Keyboard.h>
#include <SpriteBatch.h>

#include "DeviceResources.h"
#include "GameContext.h"
#include "GameState.h"
#include "Projection.h"
#include "Keyboard.h"
#include "GameStateManager.h"
#include "WICTextureLoader.h" 

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

	// �G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect>				m_pBasicEffect;

	// ViewPort
	DirectX::SimpleMath::Matrix							m_viewPort;

	// �ǔ��J����
	std::unique_ptr<FollowCamera>						m_pFollowCamera;

	// �t���A
	std::unique_ptr<Floor>								m_pFloor;

	// �v���C���[
	std::unique_ptr<Player>								m_pPlayer;

	// �G
	std::unique_ptr<Enemy>								m_pEnemy;

	// �F
	DirectX::SimpleMath::Color							m_color;

	// �̗̓e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_greenHpBarTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_redHpBarTexture;
	
	// �̗̓Q�[�W�̊�{�ʒu
	float m_gaugeDefaultPositionX;
	// �̗̓Q�[�W�̊�{�X�P�[��
	float m_gaugeDefaultScaleX;

	float m_currentGaugePositionX;
	float m_prevGaugePositionX;
	float m_currentGaugeScaleX;
	float m_prevGaugeScaleX;

	std::unique_ptr<DirectX::GeometricPrimitive> geo;
	DirectX::SimpleMath::Matrix geoMat;
	DirectX::SimpleMath::Vector3 geoVec;
};

