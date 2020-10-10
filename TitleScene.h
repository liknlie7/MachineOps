#pragma once

#include "GameScene.h"
#include "DeviceResources.h"

#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <Keyboard.h>
#include <CommonStates.h>
#include <WICTextureLoader.h>

#include "GameSceneManager.h"
#include "SceneManager.h"
#include "StepTimer.h"
#include "GameContext.h"
#include "EffectMask.h"
#include "Adx2Le.h"
#include "TitleSoundSeet.h"
#include "ResourceManager.h"

// �^�C�g���V�[��
class TitleScene : public IScene
{

public: // ��{

	// �R���X�g���N�^
	TitleScene();
	// �f�X�g���N�^
	virtual ~TitleScene();

public: // �֐�

	// ������
	eScene Initialize() override;
	// �X�V
	eScene Update(DX::StepTimer const& _timer) override;
	// �`��
	eScene Render() override;
	// �㏈��
	eScene Finalize() override;

private: // �ϐ�

	// �T�E���h
	std::weak_ptr<Adx2Le>									m_pSound;

	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_titleTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_backGroundTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_massageTexture;

	// �L�[�{�[�h�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker*				m_keyboardTracker;

	// �o�ߎ���
	float m_time;

	// �T�E���h�t�F�[�h�p
	bool m_volumeFadeFlag;
	float m_volume;
};