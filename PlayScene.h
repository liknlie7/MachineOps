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
#include "Adx2Le.h"

#include "DebugFont.h"
#include "DebugCamera.h"
#include "GridFloor.h"
#include "FollowCamera.h"
#include "Floor.h"
#include "Player.h"
#include "Enemy.h"
#include "Collision.h"
#include "MouseCursor.h"
#include "EffectMask.h"
#include "PlayerSound.h"
#include "PlaySceneSound.h"
#include "WarningEffect.h"

// �v���C�V�[���N���X
class PlayScene : public GameScene
{
public:

	// �Q�[���X�e�[�g
	enum GAME_STATE
	{
		STATE_START,		// �Q�[���J�n
		STATE_GAME,			// �Q�[����
		STATE_CONTINUE,		// ���񂾂̂ōă`�������W
		STATE_NEXT,			// ���̃E�F�[�u��
		STATE_GAMEOVERA,	// �Q�[���I�[�o�[
	};

public: // ��{

	// �R���X�g���N�^
	PlayScene();
	// �f�X�g���N�^
	virtual ~PlayScene();

public: // �A�N�Z�b�T

	// �J�����̎擾
	FollowCamera* GetCamera()
	{
		return m_pFollowCamera.get();
	}

	// �G�t�F�N�g�p�x�[�V�b�N�G�t�F�N�g���擾����֐�
	DirectX::BasicEffect* GetBatchEffect()
	{
		return m_batchEffect.get();
	}

	// �G�t�F�N�g�p�v���~�e�B�u�o�b�`���擾����֐�
	DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>* GetPrimitiveBatch()
	{
		return m_primitiveBatch.get();
	}

	// �G�t�F�N�g�p���̓��C�A�E�g���擾����֐�
	ID3D11InputLayout* GetInputLayout()
	{
		return m_inputLayout.Get();
	}

public: // �֐�

	// ������
	void Initialize() override;
	// �X�V
	void Update(DX::StepTimer const& _timer) override;
	// �`��
	void Render() override;
	// ��n��
	void Finalize() override;

	// �Q�[���̏�����
	GAME_STATE InitializeGame();

	// �Q�[�����X�^�[�g
	GAME_STATE StartGame();

	// �Q�[����
	GAME_STATE PlayGame();

	// �R���e�B�j���[
	GAME_STATE ContinueGame();

	// ���̃E�F�[�u��
	GAME_STATE NextWave();

private: // �T�u�֐�

	// ���`���
	float Lerp(float _start, float _end, float _time);

	// ���ʐ��`���
	float Slerp(float _start, float _end, float _time);

private: // �萔

	static const float DAMAGE_TIME;

private: // �ϐ�

	// �T�E���h
	std::unique_ptr<Adx2Le>					m_playSceneSound;
	std::unique_ptr<Adx2Le>					m_playerSound;

	//----- �G�t�F�N�g�p -----//
	// �G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_batchEffect;
	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_primitiveBatch;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// �Q�[���̏��
	GAME_STATE											m_gameState;

	// �G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect>				m_pBasicEffect;

	// ViewPort
	DirectX::SimpleMath::Matrix							m_viewPort;

	// �ǔ��J����
	std::unique_ptr<FollowCamera>						m_pFollowCamera;

	// �J�[�\��
	std::unique_ptr<MouseCursor>						m_pCursor;

	// �t���A
	std::unique_ptr<Floor>								m_pFloor;

	// �v���C���[
	std::unique_ptr<Player>								m_pPlayer;

	// �G
	std::unique_ptr<Enemy>								m_pEnemy;
	std::unique_ptr<Enemy>								m_pEnemies[4];
	bool bossFlag;

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
	bool m_gaugeFlag;

	// �x���G�t�F�N�g
	std::unique_ptr<WarningEffect>						m_warningEffect;

};