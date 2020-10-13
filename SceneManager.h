#pragma once

#include "StepTimer.h"
#include "Singleton.h"

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

	// 最初のシーンの設定
	void SetStartScene(eScene _scene);

	// 次のシーンのリクエスト
	void RequestScene(eScene _scene);

	// シーンの作成
	IScene* ChangeScene(eScene _scene);

private: // 変数

	// シーン
	IScene* m_pScene;

	// 次のシーン
	eScene m_nextScene;

};
