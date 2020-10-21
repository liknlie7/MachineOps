#pragma once

#include "../Common/StepTimer.h"
#include "../Common/Singleton.h"

// シーン名
enum class eScene
{
	NONE,
	TITLE,			// タイトル
	PLAY,			// プレイ
	RESULT_CLEAR,	// ゲームクリア
	RESULT_GAMEOVER,// ゲームオーバー
};

// シーンインターフェース
class IScene
{
public: // 基本

	// コンストラクタ
	IScene() = default;

	// デストラクタ
	virtual ~IScene() = default;

public: // 関数

	// 初期化
	virtual void Initialize() = 0;

	// 更新
	virtual void Update(DX::StepTimer const& _timer) = 0;

	// 描画
	virtual void Render() = 0;

	// 後処理
	virtual void Finalize() = 0;
};

// シーン管理クラス
class SceneManager : public Singleton<SceneManager>
{
	friend class Singleton<SceneManager>;

private: // 基本

	// コンストラクタ
	SceneManager(eScene _scene = eScene::TITLE);

	// デストラクタ
	~SceneManager() {};

public: // 関数

	// 現在のシーンの更新
	void Update(DX::StepTimer const& _timer);

	// 現在のシーンの描画
	void Render();

	// 次のシーンのリクエスト
	void RequestScene(eScene _scene);

private:

	// シーンの作成
	IScene* CreateScene(eScene _scene);

	// シーンの切り替え
	void ChangeScene();

private: // 変数

	// シーン
	IScene* m_pScene;

	// 次のシーン
	eScene m_nextScene;

};
