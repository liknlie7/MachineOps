#include "pch.h"

#include "SceneManager.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultClearScene.h"
#include "ResultGameOverScene.h"

// コンストラクタ
SceneManager::SceneManager(eScene _scene)
	: m_nextScene(_scene)
{
	// 最初のシーンを作成
	m_pScene = CreateScene(m_nextScene);
}

// 現在のシーンの更新
void SceneManager::Update(DX::StepTimer const & _timer)
{
	if (m_pScene == nullptr)
		return;

	if (m_nextScene != eScene::NONE)
	{
		// シーンの切り替え
		ChangeScene();
	}

	// 現在のシーン更新
	m_pScene->Update(_timer);
}

// 現在のシーンの描画
void SceneManager::Render()
{
	m_pScene->Render();
}

// シーンのリクエスト
void SceneManager::RequestScene(eScene _scene)
{
	m_nextScene = _scene;
}

// シーンの作成
IScene* SceneManager::CreateScene(eScene _scene)
{
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

	return pScene;
}

// シーンの切り替え
void SceneManager::ChangeScene()
{
	// シーンの削除
	m_pScene->Finalize();
	delete m_pScene;
	m_pScene = nullptr;

	// シーンの生成
	m_pScene = CreateScene(m_nextScene);

	// シーンの初期化
	if (m_pScene != nullptr)
		m_pScene->Initialize();

	// 次へのシーン情報初期化
	m_nextScene = eScene::NONE;
}
