#pragma once

#include "StepTimer.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultClearScene.h"
#include "ResultGameOverScene.h"

enum class eScene
{
	NONE,
	TITLE,
	PLAY,
	RESULT_CLEAR,
	RESULT_GAMEOVER,
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
	virtual eScene Initialize() = 0;

	// 更新
	virtual eScene Update(DX::StepTimer const& _timer) = 0;

	// 描画
	virtual eScene Render() = 0;

	// 後処理
	virtual eScene Finalize() = 0;
};

// シーンマネージャー
class SceneManager
{
private: // 基本

	// コンストラクタ
	SceneManager();

	// デストラクタ
	~SceneManager();

public: // 関数

	// 現在のシーンの初期化
	void Initialize();

	// 現在のシーンの更新
	void Update(DX::StepTimer const& _timer);

	// 現在のシーンの描画
	void Render();

	// 現在のシーンの後処理
	void Finalize();

	// シーンの作成
	IScene* ChangeScene(eScene _scene);

private: // 変数

	// シーン
	IScene* m_pScene;

	eScene m_nextScene;

};
