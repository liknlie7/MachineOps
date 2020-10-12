#pragma once

#include "GameScene.h"
#include "DeviceResources.h"

#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <Keyboard.h>
#include <CommonStates.h>

#include "SceneManager.h"
#include "StepTimer.h"
#include "GameContext.h"
#include "EffectMask.h"
#include "Adx2Le.h"
#include "TitleSoundSeet.h"
#include "ResourceManager.h"

class IScene;

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

private: // �萔

	// �e�N�X�`���p
	enum Texture
	{
		TITLE = 1,		// �^�C�g����
		BACK_GROUND,	// �w�i
		TEXT,			// �e�L�X�g

		ALL,
	};

private: // �ϐ�

	// �T�E���h
	std::weak_ptr<Adx2Le>									m_pSound;

	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_textures[Texture::ALL];

	// �L�[�{�[�h�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker*				m_keyboardTracker;

	// �o�ߎ���
	float m_time;

	// �T�E���h�t�F�[�h�p
	bool m_volumeFadeFlag;
	float m_volume;
};