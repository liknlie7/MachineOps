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
public: // ��{

	Weapon();
	~Weapon() {}

public: // �A�N�Z�T

	// ����̍��W�ݒ�
	void SetWeaponPos(DirectX::SimpleMath::Vector3 _pos)
	{
		m_pos = _pos;
	}

	// �e�̍��W�擾
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

public: // �֐�

	void Initialize();
	void Update(DirectX::SimpleMath::Vector3 _playerPos, float _angle);
	void Render(DirectX::SimpleMath::Matrix _view, DirectX::SimpleMath::Vector4 _color);
	void Finalize();

	// �e�̐���
	void CreateBullet(float _angle);

private: // �ϐ�

	// ����
	std::unique_ptr<DirectX::GeometricPrimitive> m_pWeapon;
	// �e
	std::unique_ptr<DirectX::GeometricPrimitive> m_pBulletGeometric;
	std::vector<std::unique_ptr<Bullet>>		 m_pBullets;

	// �ʒu
	DirectX::SimpleMath::Vector3				 m_pos;
	DirectX::SimpleMath::Vector3				 m_playerPos;
	// �s��
	DirectX::SimpleMath::Matrix					 m_matrix;

	bool bulletHitFlag;
	int bulletNumber;

};