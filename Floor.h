#pragma once

#include <Model.h>
#include <Effects.h>
#include <CommonStates.h>

#include "DeviceResources.h"
#include "SimpleMath.h"
#include "Projection.h"
#include "GameContext.h"

// 床
class Floor
{
public: // 基本

	Floor() {}
	~Floor() {}

public: // 関数

	// 初期化
	void Initialize();
	// 描画
	void Render(DirectX::SimpleMath::Matrix _view);

private:

	// モデル
	std::unique_ptr<DirectX::Model>	m_pModel;
};