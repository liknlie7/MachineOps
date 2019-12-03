#pragma once

#include <SimpleMath.h>
#include <GeometricPrimitive.h>

#include "StepTimer.h"
#include "Projection.h"
#include "GameContext.h"
#include "GameObject.h"

#include "BulletFactory.h"

// �e
class Bullet : public GameObject
{
public: // ��{

	// �R���X�g���N�^
	Bullet() {};
	Bullet(DirectX::SimpleMath::Vector3 _pos, float _angle, DirectX::SimpleMath::Vector3 _speed);
	// �f�X�g���N�^
	~Bullet() {}

public: // �A�N�Z�T

	// ���W�̎擾
	DirectX::SimpleMath::Vector3 GetPosition()
	{
		return m_pos;
	}
	// ���W�̐ݒ�
	void SetPosition(const DirectX::SimpleMath::Vector3& _pos)
	{
		m_pos = _pos;
	}

	// �p�x�̎擾
	float GetAngle()
	{
		return m_angle;
	}
	// �p�x�̐ݒ�
	void SetAngle(float _angle)
	{
		m_angle = _angle;
	}

	// �Փ˃t���O�̎擾
	bool GetHitFlag()
	{
		return m_hitFlag;
	}
	// �Փ˃t���O�̐ݒ�
	void SetHitFlag(bool _flag)
	{
		m_hitFlag = _flag;
	}

	// �g�p�����ǂ������擾����
	bool IsUsed() const
	{
		return m_used;
	}

	// �g�p�����ǂ�����ݒ肷��
	void IsUsed(bool _used)
	{
		m_used = _used;
	}


public: // �֐�

	// ������
	void Initialize(BulletFactory* _bulletFactory);
	// �X�V
	void Update() override;
	// �`��
	void Render(const DirectX::SimpleMath::Matrix& _view) override;
	// �㏈��
	void Finalize();

	// �Փ˂�����
	void OnCollision();

private: // �ϐ�

	// �e�̌`��
	DirectX::GeometricPrimitive*	m_bullet;

	// �p�x
	float m_angle;

	// �t���O
	bool m_hitFlag;
	bool m_used;
};