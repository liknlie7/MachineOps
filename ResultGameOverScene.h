#pragma once
#include "GameScene.h"
#include "DeviceResources.h"

#include <SpriteBatch.h>
#include <Keyboard.h>
#include <CommonStates.h>
#include <WICTextureLoader.h>
#include <SimpleMath.h>
#include "StepTimer.h"

// �Q�[���I�[�o�[�V�[��
class ResultGameOverScene : public GameScene
{
public: // ��{

	// �R���X�g���N�^
	ResultGameOverScene();
	// �f�X�g���N�^
	virtual ~ResultGameOverScene();

public: // �֐�

	// ������
	void Initialize() override;
	// �X�V
	void Update(DX::StepTimer const& _timer) override;
	//�`��
	void Render() override;
	// �㏈��
	void Finalize() override;

private: // �ϐ�

	// �L�[�{�[�h�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker*	m_keyboardTracker;

	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_backGroundTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_gameOverTexture;

};

