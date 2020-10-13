#include "pch.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultClearScene.h"
#include "ResultGameOverScene.h"

// �R���X�g���N�^
SceneManager::SceneManager()
	: m_pScene(nullptr)
	, m_nextScene(eScene::NONE)
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
	if (m_pScene == nullptr)
		return;

	if (m_nextScene != eScene::NONE)
	{
		m_pScene->Finalize();
		delete m_pScene;
		m_pScene = nullptr;

		m_pScene = ChangeScene(m_nextScene);
	}

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

// �ŏ��̃V�[���̐ݒ�
void SceneManager::SetStartScene(eScene _scene)
{
	m_pScene = ChangeScene(_scene);
}

// �V�[���̃��N�G�X�g
void SceneManager::RequestScene(eScene _scene)
{
	m_nextScene = _scene;
}

// �V�[���̍쐬
IScene* SceneManager::ChangeScene(eScene _scene)
{
	//if (m_pScene != nullptr)
	//	delete m_pScene;

	IScene* pScene = nullptr;

	switch (_scene)
	{
	case eScene::TITLE:

		// �^�C�g���V�[���֑J��
		pScene = new TitleScene();
		break;

	case eScene::PLAY:

		// �v���C�V�[���֑J��
		pScene = new PlayScene();
		break;

	case eScene::RESULT_CLEAR:

		// �N���A�V�[���֑J��
		pScene = new ResultClearScene();
		break;

	case eScene::RESULT_GAMEOVER:

		// �Q�[���I�[�o�[�V�[���֑J��
		pScene = new ResultGameOverScene();
		break;

	default:
		break;
	}

	// �V�[���̏�����
	if (pScene != nullptr)
		pScene->Initialize();

	m_nextScene = eScene::NONE;

	return pScene;
}
