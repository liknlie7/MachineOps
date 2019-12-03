#pragma once

#include <d3d11_1.h>
#include <DirectXMath.h>
#include <SimpleMath.h>

#include "Bullet.h"
#include "BulletFactory.h"

class IBullet
{
public:
	enum ID { NORMAL, NWAY };
	// 初期化
	virtual void Initialize(BulletFactory* _bulletFactory) = 0;
	// 発射
	virtual void Shoot(const DX::StepTimer& _timer, const DirectX::SimpleMath::Vector3& _position, const float& _angle) = 0;
	// 後始末
	virtual void Finalize() = 0;
};