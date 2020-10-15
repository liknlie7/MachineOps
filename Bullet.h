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
	Bullet();
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
		return m_isUsed;
	}

	// �g�p�����ǂ����̐ݒ�
	void SetIsUsed(bool _used)
	{
		m_isUsed = _used;
	}

	// �e�̌`���ݒ�
	void SetBulletGeometry(DirectX::GeometricPrimitive* _bulletGeometry)
	{
		m_pBulletGeometry = _bulletGeometry;
	}

	// ��]�̐ݒ�
	void SetRotation(DirectX::SimpleMath::Matrix _rotate)
	{
		m_rotate = _rotate;
	}

	// ���x�̐ݒ�
	void SetSpeed(float _speed)
	{
		m_speed = _speed;
	}

public: // �֐�

	// ������
	void Initialize(DirectX::GeometricPrimitive* _type);
	// �X�V
	void Update() override;
	void Update(const DirectX::SimpleMath::Vector3& _pos, const DirectX::SimpleMath::Vector3& _vel, const DirectX::SimpleMath::Matrix& _rotate);
	// �`��
	void Render(const DirectX::SimpleMath::Matrix& _view) override;
	// �㏈��
	void Finalize();

private: // �ϐ�

	// �e�̌`��
	DirectX::GeometricPrimitive*	m_pBulletGeometry;

	// ��]
	DirectX::SimpleMath::Matrix		m_rotate;

	// �p�x
	float m_angle;

	// �t���O
	bool m_isValid;

	// ��s����
	float m_life;

	// �e�̑��x
	float m_speed;

	// �g�p����
	bool m_isUsed;
};