#pragma once

#include "GameScene.h"
#include "DeviceResources.h"

#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <Keyboard.h>
#include <CommonStates.h>
#include <WICTextureLoader.h>

#include "GameSceneManager.h"
#include "StepTimer.h"
#include "GameContext.h"
#include "EffectMask.h"
#include "Adx2Le.h"
#include "TitleSoundSeet.h"

// �^�C�g���V�[��
class TitleScene : public GameScene
{

public: // ��{

	// �R���X�g���N�^
	TitleScene();
	// �f�X�g���N�^
	virtual ~TitleScene();

public: // �֐�

	// ������
	void Initialize() override;
	// �X�V
	void Update(DX::StepTimer const& _timer) override;
	// �`��
	void Render() override;
	// �㏈��
	void Finalize() override;

private: // �ϐ�

	// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch>	m_spriteBatch;

	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_titleTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_backGroundTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_massageTexture;

	// �L�[�{�[�h�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker*				m_keyboardTracker;

	// �o�ߎ���
	float m_time;
};