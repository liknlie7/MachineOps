#pragma once

#include "StepTimer.h"

class GameScene
{
public: // 基本

	// コンストラクタ
	GameScene() = default;
	// デストラクタ
	virtual ~GameScene() = default;

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