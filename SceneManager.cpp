#include "pch.h"
#include "SceneManager.h"

// コンストラクタ
SceneManager::SceneManager()
	: m_pScene(nullptr)
{

}

// デストラクタ
SceneManager::~SceneManager()
{

}

// 現在のシーンの初期化
void SceneManager::Initialize()
{
	m_pScene->Initialize();
}

// 現在のシーンの更新
void SceneManager::Update(DX::StepTimer const & _timer)
{
	m_pScene->Update(_timer);
}

// 現在のシーンの描画
void SceneManager::Render()
{
	m_pScene->Render();
}

// 現在のシーンの後処理
void SceneManager::Finalize()
{
	m_pScene->Finalize();
}

// シーンの作成
IScene* SceneManager::ChangeScene(eScene _scene)
{
	// いずれかのシーンが動作中
	if (m_pScene != nullptr)
	{
		// 削除する
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
