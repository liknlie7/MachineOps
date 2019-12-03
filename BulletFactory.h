#pragma once

#include <vector>
#include <SimpleMath.h>
#include <GeometricPrimitive.h>

#include "DeviceResources.h"
#include "GameContext.h"

class Bullet;

class BulletFactory
{
public: // 基本

	// コンストラクタ
	BulletFactory();
	~BulletFactory() {};

public: // アクセッサ

	// 弾の形状を取得する
	DirectX::GeometricPrimitive* GetGeometric()
	{
		return m_pBulletGeometric.get();
	}

public: // 関数

	// 初期化
	void Initialize();
	// 弾を発射する
	Bullet* Create(const DirectX::SimpleMath::Vector3& position, const float& angle);
	// 後始末
	void Finalize();

public: // 定数

	static const int BULLET_NUM = 30;

private: // 変数

	// 弾の形状
	std::unique_ptr<DirectX::GeometricPrimitive> m_pBulletGeometric;
	
	// 弾配列
	std::vector<std::unique_ptr<Bullet>> m_pBulletArray;

};

