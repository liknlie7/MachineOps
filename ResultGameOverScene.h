#pragma once

#include <SpriteBatch.h>
#include <Keyboard.h>
#include <CommonStates.h>
#include <WICTextureLoader.h>
#include <SimpleMath.h>

#include "DeviceResources.h"
#include "StepTimer.h"
#include "SceneManager.h"
#include "ResourceManager.h"

class IScene;

// �Q�[���I�[�o�[�V�[��
class ResultGameOverScene : public IScene
{
public: // ��{

	// �R���X�g���N�^
	ResultGameOverScene();

	// �f�X�g���N�^
	virtual ~ResultGameOverScene();

public: // �֐�

	// ������
	eScene Initialize() override;

	// �X�V
	eScene Update(DX::StepTimer const& _timer) override;
	
	//�`��
	eScene Render() override;
	
	// �㏈��
	eScene Finalize() override;

private: // �萔

	// �e�N�X�`��
	enum Texture
	{
		BACK_GROUND = 1,// �w�i
		TEXT,			// �e�L�X�g

		ALL,			// �S�Ẵe�N�X�`��
	};

private: // �ϐ�

	// �L�[�{�[�h�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker*	m_keyboardTracker;

	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_textures[Texture::ALL];

};

