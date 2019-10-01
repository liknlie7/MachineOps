#pragma once

#include <GeometricPrimitive.h>
#include <SimpleMath.h>
#include <Keyboard.h>
#include <Mouse.h>

#include "DeviceResources.h"
#include "StepTimer.h"
#include "Projection.h"
#include "GameContext.h"
#include "Bullet.h"

class Bullet;

class Weapon
{
public: // 基本

	// コンストラクタ
	Weapon();
	// デストラクタ
	~Weapon() {}

public: // アクセサ

	// 座標設定
	void SetWeaponPos(DirectX::SimpleMath::Vector3 _pos)
	{
		m_pos = _pos;
	}

	// 弾の座標取得
	std::vector<DirectX::SimpleMath::Vector3> GetBulletPos()
	{
		std::vector<DirectX::SimpleMath::Vector3> bulletsPos;
		for (auto& numBullet : m_pBullets)
		{
			bulletsPos.push_back(numBullet->GetPos());
		}
		return bulletsPos;
	}

	// プレイヤーの座標設定
	void SetPlayerPos(DirectX::SimpleMath::Vector3 _playerPos)
	{
		m_playerPos = _playerPos;
	}

	// 角度の設定
	void SetAngle(float _angle)
	{
		m_angle = _angle;
	}

	void SetBulletHitFlag(bool _bulletHitFlag)
	{
		bulletHitFlag = _bulletHitFlag;
	}
	void SetBulletNumber(int _bulletNumber)
	{
		bulletNumber = _bulletNumber;
	}

public: // 関数

	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Render(DirectX::SimpleMath::Matrix _view);
	// 後始末
	void Finalize();


	// 弾の生成
	void CreateBullet();

private: // 変数

	// 武器
	std::unique_ptr<DirectX::GeometricPrimitive> m_pWeapon;
	// 弾
	std::unique_ptr<DirectX::GeometricPrimitive> m_pBulletGeometric;
	std::vector<std::unique_ptr<Bullet>>		 m_pBullets;

	// 位置
	DirectX::SimpleMath::Vector3				 m_pos;
	DirectX::SimpleMath::Vector3				 m_playerPos;
	// 行列
	DirectX::SimpleMath::Matrix					 m_matrix;

	// 角度
	float										 m_angle;

	bool										 bulletHitFlag;
	int											 bulletNumber;

};