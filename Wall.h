#pragma once

#include <Model.h>
#include <SimpleMath.h>
#include <Effects.h>

#include "DeviceResources.h"
#include "GameObject.h"
#include "GameContext.h"
#include "Projection.h"

// 壁
class Wall : public GameObject
{
public: // 基本

	// コンストラクタ
	Wall(const std::string& _tag);
	// デストラクタ
	~Wall() {};

public: // 関数

	// 初期化
	void Initialize();
	// 更新
	void Update() override;
	// 描画
	void Render(const DirectX::SimpleMath::Matrix& _view) override;

private: // 変数

	// モデル
	std::unique_ptr<DirectX::Model>	m_pModel;
};

