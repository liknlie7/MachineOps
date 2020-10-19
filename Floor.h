#pragma once

#include <Model.h>
#include <SimpleMath.h>

#include "Collision.h"
#include "GameObject.h"

// 床
class Floor : public GameObject
{
public: // 基本

	// コンストラクタ
	Floor() {};

	// デストラクタ
	~Floor() {}

public: // 関数

	// 初期化
	void Initialize();

	// 更新
	void Update() override {};

	// 描画
	void Render(const DirectX::SimpleMath::Matrix& _view) override;

public: // アクセサ

	// 三角形の取得
	Collision::Triangle GetTriangle(int _number) const
	{
		if (_number == 0)
			return Collision::Triangle(m_vector[0], m_vector[2], m_vector[1]);
		else
			return Collision::Triangle(m_vector[0], m_vector[3], m_vector[2]);
	}


public: // 定数

	// 横幅
	static const float AREA_WIDTH;
	
	// 縦幅
	static const float AREA_HEIGHT;

private: // 変数

	// モデル
	std::weak_ptr<DirectX::Model>	m_pModel;

	// 頂点
	DirectX::SimpleMath::Vector3	m_vector[4];
};