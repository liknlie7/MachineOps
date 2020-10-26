#pragma once

#include <SimpleMath.h>
#include <GeometricPrimitive.h>

#include "GameObject.h"

// �e
class Bullet :public GameObject
{
public: // ��{

	// �R���X�g���N�^
	Bullet();
	
	// �f�X�g���N�^
	~Bullet() {}

public: // �֐�

	// ������
	void Initialize() {};
	
	// �X�V
	void Update() override;
	
	// �`��
	void Render(const DirectX::SimpleMath::Matrix& _view) override;
	
	// �㏈��
	void Finalize() {};

public: // �A�N�Z�T

	// �p�x�̐ݒ�
	void SetAngle(const float _angle)
	{
		m_angle = _angle;
	}
	
	// �g�p�����ǂ����̎擾
	bool GetIsUsed() const
	{
		return m_isUsed;
	}

	// �g�p�����ǂ����̐ݒ�
	void SetIsUsed(const bool _used)
	{
		m_isUsed = _used;
	}

	// �e�̌`���ݒ�
	void SetBulletGeometry(DirectX::GeometricPrimitive* _bulletGeometry)
	{
		m_pBulletGeometry = _bulletGeometry;
	}

	// ���x�̐ݒ�
	void SetSpeed(const float _speed)
	{
		m_speed = _speed;
	}

	// �^�O�̐ݒ�
	void SetTag(const std::string& _tag)
	{
		m_tag = _tag;
	}

	// �^�O�̎擾
	const std::string& GetTag() const
	{
		return m_tag;
	}

private: // �萔

	// �e�̐�������
	static const float BULLET_LIFE;

private: // �ϐ�

	// �e�̌`��
	DirectX::GeometricPrimitive*	m_pBulletGeometry;

	// ��]
	DirectX::SimpleMath::Matrix		m_rotate;

	// �p�x
	float m_angle;

	// ��s����
	float m_life;

	// �e�̑��x
	float m_speed;

	// �^�O
	std::string m_tag;

	// �g�p����
	bool m_isUsed;
};