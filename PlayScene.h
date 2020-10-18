#pragma once

#include <SimpleMath.h>
#include <Effects.h>
#include <SpriteBatch.h>

#include "SceneManager.h"
#include "WICTextureLoader.h" 
#include "StepTimer.h"
#include "Adx2Le.h"
#include "FollowCamera.h"
#include "Floor.h"
#include "Wall.h"
#include "Player.h"
#include "Enemy.h"
#include "MouseCursor.h"
#include "WarningEffect.h"
#include "BulletManager.h"

// �v���C�V�[���N���X
class PlayScene : public IScene
{
public:

	// �Q�[���X�e�[�g
	enum GAME_STATE
	{
		STATE_START,		// �Q�[���J�n
		STATE_GAME,			// �Q�[����
	};

	// �E�F�[�u
	enum WAVE_STATE
	{
		NORMAL_WAVE,		// �ʏ�E�F�[�u
		BOSS_WAVE,			// �{�X�E�F�[�u
	};

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
	void Finalize() override {};

private: // �T�u�֐�

	// ���`���
	float Lerp(float _start, float _end, float _time);

private: // �萔

	// �G�l�~�[(�{�X)�����ʒu
	static const DirectX::SimpleMath::Vector3 ENEMY_BOSS_INIT_POS;

	// ���C�t�Q�[�W�����ɂ����鎞��
	static const float DAMAGE_TIME;

	// HP�Q�[�W�X�P�[���l
	static const float HP_SCALE_X;
	static const float HP_SCALE_Y;

	// HP�Q�[�W�ʒu
	static const DirectX::SimpleMath::Vector2 HP_RED_POS;
	static const DirectX::SimpleMath::Vector2 HP_GREEN_POS;

	// �����Q�[�W�p
	static const DirectX::SimpleMath::Vector4 HP_GAUGE_COLOR;

	// �e�N�X�`��
	enum Texture
	{
		GREEN_HP,	// ��HP
		RED_HP,		// ��HP

		ALL,		// �S�Ẵe�N�X�`��
	};

private: // �ϐ�

	// �T�E���h
	std::weak_ptr<Adx2Le>								m_pSound;

	// �G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect>				m_batchEffect;

	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_primitiveBatch;

	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			m_inputLayout;
	// �Q�[���̏��
	GAME_STATE											m_gameState;

	// �E�F�[�u�̏��
	WAVE_STATE											m_waveState;

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

	// ��
	std::unique_ptr<Wall>								m_pWall;

	// �v���C���[
	std::unique_ptr<Player>								m_pPlayer;

	// �G�l�~�[
	std::unique_ptr<Enemy>								m_pEnemy;

	// �e�Ǘ��p
	std::unique_ptr<BulletManager>						m_pBulletManager;

	// ����
	float												m_totalTime;

	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_textures[Texture::ALL];

	// �̗̓Q�[�W�f�t�H���g�T�C�Y
	float												m_defaultGaugeScaleX;

	// ���݂̗̑̓Q�[�W�X�P�[��
	float												m_currentGaugeScaleX;
	
	// �O�̗̑̓Q�[�W�X�P�[��
	float												m_prevGaugeScaleX;
	
	// ���킶�팸������Q�[�W
	float												m_lightGreenGaugeRate;
	bool												m_gaugeFlag;

	// �x���G�t�F�N�g
	std::unique_ptr<WarningEffect>						m_warningEffect;
};