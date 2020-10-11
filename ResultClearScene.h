#pragma once

#include <SpriteBatch.h>
#include <Keyboard.h>
#include <CommonStates.h>
#include <WICTextureLoader.h>
#include <SimpleMath.h>
#include "StepTimer.h"

#include "GameScene.h"
#include "DeviceResources.h"
#include "SceneManager.h"

class IScene;

// �N���A�V�[��
class ResultClearScene : public IScene
{
public: // ��{

	// �R���X�g���N�^
	ResultClearScene();

	// �f�X�g���N�^
	virtual ~ResultClearScene();

public: // �֐�

	// ������
	eScene Initialize() override;
	
	// �X�V
	eScene Update(DX::StepTimer const& _timer) override;
	
	//�`��
	eScene Render() override;
	
	// �㏈��
	eScene Finalize() override;

private: // �ϐ�

	// �L�[�{�[�h�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker*	m_keyboardTracker;

	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_backGroundTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_clearTexture;
};

