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

	Weapon();
	~Weapon() {}

public: // アクセサ

	// 武器の座標設定
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

	
	void SetBulletHitFlag(bool _bulletHitFlag)
	{
		bulletHitFlag = _bulletHitFlag;
	}
	void SetBulletNumber(int _bulletNumber)
	{
		bulletNumber = _bulletNumber;
	}

public: // 関数

	void Initialize();
	void Update(DirectX::SimpleMath::Vector3 _playerPos, float _angle);
	void Render(DirectX::SimpleMath::Matrix _view, DirectX::SimpleMath::Vector4 _color);
	void Finalize();

	// 弾の生成
	void CreateBullet(float _angle);

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

	bool bulletHitFlag;
	int bulletNumber;

};