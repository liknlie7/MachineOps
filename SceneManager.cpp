#include "pch.h"
#include "SceneManager.h"

// �R���X�g���N�^
SceneManager::SceneManager()
	: m_pScene(nullptr)
{

}

// �f�X�g���N�^
SceneManager::~SceneManager()
{

}

// ���݂̃V�[���̏�����
void SceneManager::Initialize()
{
	m_pScene->Initialize();
}

// ���݂̃V�[���̍X�V
void SceneManager::Update(DX::StepTimer const & _timer)
{
	m_pScene->Update(_timer);
}

// ���݂̃V�[���̕`��
void SceneManager::Render()
{
	m_pScene->Render();
}

// ���݂̃V�[���̌㏈��
void SceneManager::Finalize()
{
	m_pScene->Finalize();
}

// �V�[���̍쐬
IScene* SceneManager::ChangeScene(eScene _scene)
{
	// �����ꂩ�̃V�[�������쒆
	if (m_pScene != nullptr)
	{
		// �폜����
		delete m_pScene;
	}

	switch (_scene)
	{
	case eScene::TITLE:

		m_pScene = new TitleScene();
		break;

	case eScene::PLAY:

		m_pScene = new PlayScene();
		break;
	
	case eScene::RESULT_CLEAR:

		m_pScene = new ResultClearScene();
		break;

	case eScene::RESULT_GAMEOVER:

		m_pScene = new ResultGameOverScene();
		break;

	default:
		break;
	}
}
