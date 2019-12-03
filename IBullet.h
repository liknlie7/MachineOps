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
	// èâä˙âª
	virtual void Initialize(BulletFactory* _bulletFactory) = 0;
	// î≠éÀ
	virtual void Shoot(const DX::StepTimer& _timer, const DirectX::SimpleMath::Vector3& _position, const float& _angle) = 0;
	// å„énññ
	virtual void Finalize() = 0;
};