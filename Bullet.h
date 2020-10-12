#pragma once

#include <SimpleMath.h>
#include <GeometricPrimitive.h>

#include "DeviceResources.h"
#include "Projection.h"
#include "GameContext.h"
#include "GameObject.h"

// �e
class Bullet :public GameObject
{
public: // ��{

	// �R���X�g���N�^
	Bullet(const DirectX::SimpleMath::Vector3& _pos, const DirectX::SimpleMath::Vector3& _vel, const float& _angle);
	// �f�X�g���N�^
	~Bullet() {}

public: // �A�N�Z�T

	// �p�x�̐ݒ�
	void SetAngle(const float _angle)
	{
		m_angle = _angle;
	}

	// �t���O�擾
	bool GetIsValid() const
	{
		return m_isValid;
	}
	// �t���O�ݒ�
	void SetIsValid(const bool& _flag)
	{
		m_isValid = _flag;
	}

	// ��s���Ԃ̎擾
	float GetLife() const
	{
		return m_life;
	}

	// �g�p�����ǂ����̎擾
	bool GetIsUsed()
	{
		return m_used;
	}

	// �g�p�����ǂ����̐ݒ�
	void SetIsUsed(bool _used)
	{
		m_used = _used;
	}

	//// �e�̌`���ݒ�
	//void SetBulletType(DirectX::GeometricPrimitive* _bulletType)
	//{
	//	m_bullet = _bulletType;
	//}

public: // �֐�

	// ������
	void Initialize(DirectX::GeometricPrimitive* _type);
	// �X�V
	void Update() override;
	// �`��
	void Render(const DirectX::SimpleMath::Matrix& _view) override;
	// �㏈��
	void Finalize();

private: // �ϐ�

	// �e�̌`��
	//DirectX::GeometricPrimitive*	m_bullet;

	// ��]
	DirectX::SimpleMath::Matrix		m_rotate;

	// �p�x
	float m_angle;

	// �t���O
	bool m_isValid;

	// ��s����
	float m_life;

	// �g�p����
	bool m_used;
};