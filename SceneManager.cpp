#include "pch.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultClearScene.h"
#include "ResultGameOverScene.h"

// コンストラクタ
SceneManager::SceneManager()
	: m_pScene(nullptr)
	, m_nextScene(eScene::NONE)
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

// 最初のシーンの設定
void SceneManager::SetStartScene(eScene _scene)
{
	m_pScene = ChangeScene(_scene);
}

// シーンのリクエスト
void SceneManager::RequestScene(eScene _scene)
{
	m_nextScene = _scene;
}

// シーンの作成
IScene* SceneManager::ChangeScene(eScene _scene)
{
	//if (m_pScene != nullptr)
	//	delete m_pScene;

	IScene* pScene = nullptr;

	switch (_scene)
	{
	case eScene::TITLE:

		// タイトルシーンへ遷移
		pScene = new TitleScene();
		break;

	case eScene::PLAY:

		// プレイシーンへ遷移
		pScene = new PlayScene();
		break;

	case eScene::RESULT_CLEAR:

		// クリアシーンへ遷移
		pScene = new ResultClearScene();
		break;

	case eScene::RESULT_GAMEOVER:

		// ゲームオーバーシーンへ遷移
		pScene = new ResultGameOverScene();
		break;

	default:
		break;
	}

	// シーンの初期化
	if (pScene != nullptr)
		pScene->Initialize();

	m_nextScene = eScene::NONE;

	return pScene;
}
