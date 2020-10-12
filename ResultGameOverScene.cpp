#include "pch.h"
#include "ResultGameOverScene.h"

#include "GameContext.h"
//#include "GameSceneManager.h"

// �R���X�g���N�^
ResultGameOverScene::ResultGameOverScene()
{
	m_keyboardTracker = GameContext::Get<DirectX::Keyboard::KeyboardStateTracker>();
}

// �f�X�g���N�^
ResultGameOverScene::~ResultGameOverScene()
{
}

// ������
eScene ResultGameOverScene::Initialize()
{
	// �e�N�X�`���f�[�^���󂯎��
	m_textures[BACK_GROUND] = ResourceManager::GetInstance().GetTexture(L"Resources\\Textures\\ResultBackGround.png");
	m_textures[TEXT] = ResourceManager::GetInstance().GetTexture(L"Resources\\Textures\\GameOver.png");

	return eScene::RESULT_GAMEOVER;
}

// �X�V
eScene ResultGameOverScene::Update(DX::StepTimer const & _timer)
{
	_timer;
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	m_keyboardTracker->Update(keyState);

	if (m_keyboardTracker->pressed.Space)
	{
		//GameSceneManager* gameSceneManager = GameContext::Get<GameSceneManager>();
		//gameSceneManager->RequestScene("Title");
	}

	return eScene::RESULT_GAMEOVER;
}

// �`��
eScene ResultGameOverScene::Render()
{
	// �X�v���C�g�o�b�`�̎擾
	DirectX::SpriteBatch* spriteBatch = GameContext::Get<DirectX::SpriteBatch>();

	// �e�N�X�`���`��
	spriteBatch->Begin();
	spriteBatch->Draw(m_textures[BACK_GROUND].Get(), DirectX::SimpleMath::Vector2::Zero, nullptr, DirectX::Colors::White, 0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(1.2f, 1.2f));
	spriteBatch->Draw(m_textures[TEXT].Get(), DirectX::SimpleMath::Vector2(330, 250), nullptr, DirectX::Colors::White, 0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(0.8f, 0.8f));
	spriteBatch->End();

	return eScene::RESULT_GAMEOVER;
}

// �㏈��
eScene ResultGameOverScene::Finalize()
{
	return eScene::RESULT_GAMEOVER;
}
