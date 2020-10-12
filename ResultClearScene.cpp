#include "pch.h"
#include "ResultClearScene.h"

#include "GameContext.h"
//#include "GameSceneManager.h"

// �R���X�g���N�^
ResultClearScene::ResultClearScene()

{
	m_keyboardTracker = GameContext::Get<DirectX::Keyboard::KeyboardStateTracker>();
}

// �f�X�g���N�^
ResultClearScene::~ResultClearScene()
{
}

// ������
eScene ResultClearScene::Initialize()
{
	// �e�N�X�`���f�[�^���󂯎��
	m_textures[BACK_GROUND] = ResourceManager::GetInstance().GetTexture(L"Resources\\Textures\\ResultBackGround.png");
	m_textures[TEXT] = ResourceManager::GetInstance().GetTexture(L"Resources\\Textures\\GameClear.png");

	return eScene::RESULT_CLEAR;
}

// �X�V
eScene ResultClearScene::Update(DX::StepTimer const & _timer)
{
	_timer;

	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	m_keyboardTracker->Update(keyState);

	if (m_keyboardTracker->pressed.Space)
	{
		//GameSceneManager* gameSceneManager = GameContext::Get<GameSceneManager>();
		//gameSceneManager->RequestScene("Title");
	}

	return eScene::RESULT_CLEAR;
}

// �`��
eScene ResultClearScene::Render()
{
	// �X�v���C�g�o�b�`�̎擾
	DirectX::SpriteBatch* spriteBatch = GameContext::Get<DirectX::SpriteBatch>();

	// �e�N�X�`���`��
	spriteBatch->Begin();
	spriteBatch->Draw(m_textures[BACK_GROUND].Get(), DirectX::SimpleMath::Vector2::Zero, nullptr, DirectX::Colors::White, 0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(1.2f, 1.2f));
	spriteBatch->Draw(m_textures[TEXT].Get(), DirectX::SimpleMath::Vector2(290, 250), nullptr, DirectX::Colors::White, 0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(0.8f, 0.8f));
	spriteBatch->End();

	return eScene::RESULT_CLEAR;
}

// �㏈��
eScene ResultClearScene::Finalize()
{
	return eScene::RESULT_CLEAR;
}
