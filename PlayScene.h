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
#include "GameScene.h"
#include "Projection.h"
#include "Keyboard.h"
#include "GameSceneManager.h"
#include "WICTextureLoader.h" 
#include "StepTimer.h"

#include "DebugFont.h"
#include "DebugCamera.h"
#include "GridFloor.h"
#include "FollowCamera.h"
#include "Floor.h"
#include "Player.h"
#include "Enemy.h"
#include "Collision.h"

// �v���C�V�[���N���X
class PlayScene : public GameScene
{
public: // ��{

	// �R���X�g���N�^
	PlayScene();
	// �f�X�g���N�^
	virtual ~PlayScene();

public: // �֐�

	// ������
	void Initialize() override;
	// �X�V
	void Update(DX::StepTimer const& _timer) override;
	// �`��
	void Render() override;
	// ��n��
	void Finalize() override;

	float Lerp(float _start, float _end, float _time);

private: // �萔

	static const float DAMAGE_TIME;

private: // �ϐ�

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

	// ����
	float												m_totalTime;

	// �̗̓e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_greenHpBarTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_redHpBarTexture;

	// �̗̓Q�[�W�f�t�H���g�T�C�Y
	float m_defaultGaugeScaleX;
	// ���݂̗̑̓Q�[�W�X�P�[��
	float m_currentGaugeScaleX;
	// �O�̗̑̓Q�[�W�X�P�[��
	float m_prevGaugeScaleX;
	// ���킶�팸������Q�[�W
	float m_lightGreenGaugeRate;

	std::unique_ptr<DirectX::GeometricPrimitive> geo;
	DirectX::SimpleMath::Matrix geoMat;
	DirectX::SimpleMath::Vector3 geoVec;
};