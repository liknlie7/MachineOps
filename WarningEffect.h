#pragma once

#include <SimpleMath.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>

#include "WarningLine.h"

class WarningEffect
{
public: // 基本

	// コンストラクタ
	WarningEffect();
	// デストラクタ
	~WarningEffect() {};

public: // 関数

	// 初期化
	void Initialize();
	// 更新
	void Update(float _elapsedTime);
	// 描画
	void Render();

private: // 変数

	std::unique_ptr<WarningLine>		m_pLine;
};

