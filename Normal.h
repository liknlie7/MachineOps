#pragma once

#include "IBullet.h"
#include "Weapon.h"

class Weapon;
class Enemy;

class Normal : public IBullet
{
public:

	// �R���X�g���N�^
	Normal(Weapon* player = nullptr, Enemy* enemy = nullptr);

public:

	// ������
	void Initialize(BulletFactory* _bulletFactory) override;
	// �e�𔭎�
	void Shoot(const DX::StepTimer& _timer, const DirectX::SimpleMath::Vector3& _position, const float& _angle) override;
	// ��n��
	void Finalize() override;

private:

	// �v���C���[�̕���
	Weapon* m_player;
	// �G
	Enemy* m_enemy;
	// BulletFactory
	BulletFactory* m_bulletFactory;
};