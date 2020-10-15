#pragma once

#include <SpriteBatch.h>
#include <Keyboard.h>
#include <SimpleMath.h>

#include "SceneManager.h"
#include "StepTimer.h"
#include "Adx2Le.h"

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
	void Initialize() override;
	
	// �X�V
	void Update(DX::StepTimer const& _timer) override;
	
	// �`��
	void Render() override;
	
	// �㏈��
	void Finalize() override {};

private: // �萔

	// �e�N�X�`���p
	enum Texture
	{
		TITLE = 1,		// �^�C�g����
		BACK_GROUND,	// �w�i
		TEXT,			// �e�L�X�g

		ALL,
	};

	// �^�C�g���ʒu
	static const DirectX::SimpleMath::Vector2 TITLE_POSITION;

	// �^�C�g���g�嗦
	static const DirectX::SimpleMath::Vector2 TITLE_SCALE;

	// �e�L�X�g�ʒu
	static const DirectX::SimpleMath::Vector2 TEXT_POSITION;

	// �e�L�X�g�g�嗦
	static const DirectX::SimpleMath::Vector2 TEXT_SCALE;

private: // �ϐ�

	// �T�E���h
	std::weak_ptr<Adx2Le>									m_pSound;

	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_pTextures[Texture::ALL];

	// �L�[�{�[�h�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker*				m_pKeyboardTracker;

	// �o�ߎ���
	float m_time;
};