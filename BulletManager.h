#pragma once

#include <SimpleMath.h>
#include <GeometricPrimitive.h>

#include "Bullet.h"

// 弾管理クラス
class BulletManager
{
public: // 基本

	// コンストラクタ
	BulletManager();

	// デストラクタ
	~BulletManager();

public: // アクセサ

	// 弾の形状の取得
	DirectX::GeometricPrimitive* GetBulletGeometry(int _geometryType)
	{
		return m_pBulletGeometry[_geometryType].get();
	}

public: // 関数

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Render(const DirectX::SimpleMath::Matrix& _view);

	// 弾の生成
	//Bullet* Create(const DirectX::SimpleMath::Vector3& _pos, const DirectX::SimpleMath::Vector3& _vec, const float& _angle);

	// 発射
	void Shot(const DirectX::SimpleMath::Vector3& _pos, const float& _speed, const DirectX::SimpleMath::Matrix& _rotate, DirectX::GeometricPrimitive* _bulletGeometry);

	// 後処理
	void Finalize();

public: // 定数

	// 弾の形状
	enum BulletType
	{
		SPHERE = 1,	// 球
		BOX,		// ボックス

		ALL,		// 全ての形状
	};

private:
	// 弾の数
	static const int NUM_BULLET;

	// 丸い弾半径
	static const float SPHERE_BULLET_RADIUS;

	// 四角い弾サイズ
	static const DirectX::SimpleMath::Vector3 BOX_BULLET_SIZE;


private: // 変数

	// 弾の形状
	std::unique_ptr<DirectX::GeometricPrimitive> m_pBulletGeometry[BulletType::ALL];

	// 弾配列
	std::vector<std::unique_ptr<Bullet>>		 m_pBullets;
};

