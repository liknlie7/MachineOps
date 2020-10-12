#pragma once

#include <GeometricPrimitive.h>
#include <SimpleMath.h>
#include <Keyboard.h>
#include <Mouse.h>

#include "DeviceResources.h"
#include "Projection.h"
#include "GameContext.h"
#include "GameObject.h"
#include "Bullet.h"

class Weapon : public GameObject
{
public: // 基本

	// コンストラクタ
	Weapon();
	// デストラクタ
	~Weapon() {}

public: // アクセサ

	// 座標設定
	void SetWeaponPos(const DirectX::SimpleMath::Vector3& _pos)
	{
		m_position = _pos;
	}

	// 弾の座標取得
	//std::vector<DirectX::SimpleMath::Vector3> GetBulletPos() const
	//{
	//	std::vector<DirectX::SimpleMath::Vector3> bulletsPos;
	//	for (auto& numBullet : m_pBullets)
	//	{
	//		bulletsPos.push_back(numBullet->GetPosition());
	//	}
	//	return bulletsPos;
	//}

	// プレイヤーの座標設定
	void SetPlayerPos(const DirectX::SimpleMath::Vector3& _playerPos)
	{
		m_playerPos = _playerPos;
	}

	// 角度の設定
	void SetAngle(const float& _angle)
	{
		m_angle = _angle;
	}

	void SetBulletHitFlag(const bool& _isHitFlag)
	{
		bulletHitFlag = _isHitFlag;
	}
	void SetBulletNumber(const int& _bulletNumber)
	{
		bulletNumber = _bulletNumber;
	}

public: // 関数

	// 初期化
	void Initialize();
	// 更新
	void Update() override;
	// 描画
	void Render(const DirectX::SimpleMath::Matrix& _view) override;
	// 後始末
	void Finalize();
	
	// 弾の生成
	void CreateBullet();

	void BulletOnCollision(int _number);

private: // 変数

	// 武器
	std::unique_ptr<DirectX::GeometricPrimitive> m_pWeapon;
	// 弾
	std::unique_ptr<DirectX::GeometricPrimitive> m_pBulletGeometric;
	//std::vector<std::unique_ptr<Bullet>>		 m_pBullets;

	// プレイヤーの位置
	DirectX::SimpleMath::Vector3				 m_playerPos;

	// 角度
	float										 m_angle;

	bool										 bulletHitFlag;
	int											 bulletNumber;

};