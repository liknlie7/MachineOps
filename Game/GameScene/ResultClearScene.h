#pragma once

#include <Keyboard.h>
#include <WICTextureLoader.h>

#include "../Common/StepTimer.h"
#include "../Manager/Scenemanager.h"

class IScene;

// �N���A�V�[��
class ResultClearScene : public IScene
{
public: // ��{

	// �R���X�g���N�^
	ResultClearScene();

	// �f�X�g���N�^
	virtual ~ResultClearScene() {};

public: // �֐�

	// ������
	void Initialize() override;
	
	// �X�V
	void Update(DX::StepTimer const& _timer) override;
	
	//�`��
	void Render() override;
	
	// �㏈��
	void Finalize() override {};
	
private: // �萔

	// �e�N�X�`��
	enum Texture
	{
		BACK_GROUND = 1,	// �w�i
		TEXT,				// �e�L�X�g

		ALL,				// �S�Ẵe�N�X�`��
	};

private: // �ϐ�

	// �L�[�{�[�h�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker*	m_keyboardTracker;

	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_textures[Texture::ALL];
};

