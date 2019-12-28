#pragma once

#include <Model.h>
#include <Effects.h>
#include <CommonStates.h>

#include "DeviceResources.h"
#include "SimpleMath.h"
#include "Projection.h"
#include "GameContext.h"
#include "Collision.h"

// 床
class Floor
{
public: // 基本

	// コンストラクタ
	Floor() {}
	// デストラクタ
	~Floor() {}

public: // アクセサ

	// 三角形の取得
	Collision::Triangle GetTriangle(int _number) const
	{
		if (_number == 0)
			return Collision::Triangle(m_vector[0], m_vector[2], m_vector[1]);
		else
			return Collision::Triangle(m_vector[0], m_vector[3], m_vector[2]);
	}

public: // 関数

	// 初期化
	void Initialize();
	// 描画
	void Render(DirectX::SimpleMath::Matrix _view);

public: // 定数

	// 横幅
	static const float AREA_WIDTH;
	// 縦幅
	static const float AREA_HEIGHT;

private: // 変数

	// モデル
	std::unique_ptr<DirectX::Model>	m_pModel;

	// 三角形
	//Collision::Triangle				m_tri[2];
	// 頂点
	DirectX::SimpleMath::Vector3	m_vector[4];
};