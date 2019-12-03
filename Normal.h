#pragma once

#include "IBullet.h"
#include "Weapon.h"

class Weapon;
class Enemy;

class Normal : public IBullet
{
public:

	// コンストラクタ
	Normal(Weapon* player = nullptr, Enemy* enemy = nullptr);

public:

	// 初期化
	void Initialize(BulletFactory* _bulletFactory) override;
	// 弾を発射
	void Shoot(const DX::StepTimer& _timer, const DirectX::SimpleMath::Vector3& _position, const float& _angle) override;
	// 後始末
	void Finalize() override;

private:

	// プレイヤーの武器
	Weapon* m_player;
	// 敵
	Enemy* m_enemy;
	// BulletFactory
	BulletFactory* m_bulletFactory;
};