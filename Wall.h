#pragma once

#include <Model.h>

#include "GameObject.h"
#include "Collision.h"

// 壁
class Wall : public GameObject
{
public: // 基本

	// コンストラクタ
	Wall() {};

	// デストラクタ
	~Wall() {};

public: // 関数

	// 初期化
	void Initialize();
	
	// 更新
	void Update()override {};
	
	// 描画
	void Render(const DirectX::SimpleMath::Matrix& _view) override;

private:

	// 壁の作成
	void CreateWall();

public: // アクセサ

	// 当たり判定の取得
	Collision::Box GetCollider(int _num) const
	{
		return m_collider[_num];
	}

public: // 定数

	// 壁の位置
	enum PLACE
	{
		TOP_RIGHT = 0,		// 上右側
		TOP_LEFT,			// 上左側
		BOTTOM_RIGHT,		// 下右側
		BOTTOM_LEFT,		// 下左側
		LEFT_TOP,			// 左上側
		LEFT_BOTTOM,		// 左下側
		RIGHT_TOP,			// 右上側
		RIGHT_BOTTOM,		// 右下側

		ALL_PLACE,
	};

private: // 変数

	// モデル
	std::weak_ptr<DirectX::Model>				 m_pModel;

	// コライダー
	Collision::Box								 m_collider[ALL_PLACE];
};

