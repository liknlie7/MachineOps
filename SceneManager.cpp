#include "pch.h"

#include "SceneManager.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultClearScene.h"
#include "ResultGameOverScene.h"

// �R���X�g���N�^
SceneManager::SceneManager(eScene _scene)
	: m_nextScene(_scene)
{
	// �ŏ��̃V�[�����쐬
	m_pScene = CreateScene(m_nextScene);
}

// ���݂̃V�[���̍X�V
void SceneManager::Update(DX::StepTimer const & _timer)
{
	if (m_pScene == nullptr)
		return;

	if (m_nextScene != eScene::NONE)
	{
		// �V�[���̐؂�ւ�
		ChangeScene();
	}

	// ���݂̃V�[���X�V
	m_pScene->Update(_timer);
}

// ���݂̃V�[���̕`��
void SceneManager::Render()
{
	m_pScene->Render();
}

// �V�[���̃��N�G�X�g
void SceneManager::RequestScene(eScene _scene)
{
	m_nextScene = _scene;
}

// �V�[���̍쐬
IScene* SceneManager::CreateScene(eScene _scene)
{
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

	return pScene;
}

// �V�[���̐؂�ւ�
void SceneManager::ChangeScene()
{
	// �V�[���̍폜
	m_pScene->Finalize();
	delete m_pScene;
	m_pScene = nullptr;

	// �V�[���̐���
	m_pScene = CreateScene(m_nextScene);

	// �V�[���̏�����
	if (m_pScene != nullptr)
		m_pScene->Initialize();

	// ���ւ̃V�[����񏉊���
	m_nextScene = eScene::NONE;
}
