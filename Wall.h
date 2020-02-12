#pragma once

#include <Model.h>
#include <SimpleMath.h>
#include <Effects.h>

#include "DeviceResources.h"
#include "GameObject.h"
#include "GameContext.h"
#include "Projection.h"
#include "Collision.h"

#include <GeometricPrimitive.h>

// 壁
class Wall : public GameObject
{

public: // 基本

	// コンストラクタ
	Wall(const std::string& _tag);
	// デストラクタ
	~Wall() {};

public: // アクセサ

	// 当たり判定の取得
	Collision::Box GetCollider(int _num) const
	{
		return m_collider[_num];
	}

public: // 関数

	// 初期化
	void Initialize();
	// 更新
	void Update()override {};
	// 描画
	void Render(const DirectX::SimpleMath::Matrix& _view) override;

public: // 定数

	enum PLACE
	{
		TOP,		// 上側
		BOTTOM,		// 下側
		LEFT,		// 左側
		RIGHT,		// 右側

		ALL_PLACE,
	};

private: // 変数

	// モデル
	std::unique_ptr<DirectX::Model>	m_pModel;

	// コライダー
	Collision::Box					m_collider[ALL_PLACE];

	std::unique_ptr<DirectX::GeometricPrimitive> m_test;
};

