#include "pch.h"

#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <CommonStates.h>

#include "ResultGameOverScene.h"
#include "GameContext.h"
#include "DeviceResources.h"
#include "ResourceManager.h"

// �R���X�g���N�^
ResultGameOverScene::ResultGameOverScene()
{
	// �L�[�{�[�h�擾
	m_keyboardTracker = GameContext::Get<DirectX::Keyboard::KeyboardStateTracker>();
}

// ������
void ResultGameOverScene::Initialize()
{
	// �e�N�X�`���f�[�^���󂯎��
	m_textures[BACK_GROUND] = ResourceManager::GetInstance()->GetTexture(L"Resources\\Textures\\ResultBackGround.png");
	m_textures[TEXT] = ResourceManager::GetInstance()->GetTexture(L"Resources\\Textures\\GameOver.png");
}

// �X�V
void ResultGameOverScene::Update(DX::StepTimer const & _timer)
{
	_timer;
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	m_keyboardTracker->Update(keyState);

	// �X�y�[�X�L�[�������ꂽ��
	if (m_keyboardTracker->pressed.Space)
	{
		// �^�C�g���֑J�ڂ���
		SceneManager::GetInstance()->RequestScene(eScene::TITLE);
	}
}

// �`��
void ResultGameOverScene::Render()
{
	// �X�v���C�g�o�b�`�̎擾
	DirectX::SpriteBatch* spriteBatch = GameContext::Get<DirectX::SpriteBatch>();

	// �e�N�X�`���`��
	spriteBatch->Begin();
	spriteBatch->Draw(m_textures[BACK_GROUND].Get(), DirectX::SimpleMath::Vector2::Zero, nullptr, DirectX::Colors::White, 0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(1.2f, 1.2f));
	spriteBatch->Draw(m_textures[TEXT].Get(), DirectX::SimpleMath::Vector2(330, 250), nullptr, DirectX::Colors::White, 0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(0.8f, 0.8f));
	spriteBatch->End();
}
