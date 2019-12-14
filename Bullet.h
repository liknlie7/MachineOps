#pragma once

#include <SimpleMath.h>
#include <GeometricPrimitive.h>

#include "Projection.h"
#include "GameContext.h"
#include "GameObject.h"

// �e
class Bullet :public GameObject
{
public: // ��{

	// �R���X�g���N�^
	Bullet(DirectX::SimpleMath::Vector3 _pos, float _angle, DirectX::SimpleMath::Vector3 _speed);
	// �f�X�g���N�^
	~Bullet() {}

public: // �A�N�Z�T

	// ���W�擾
	DirectX::SimpleMath::Vector3 GetPos()
	{
		return m_pos;
	}
	// ���W�ݒ�
	void SetPos(const DirectX::SimpleMath::Vector3& _pos)
	{
		m_pos = _pos;
	}

	// �t���O�擾
	bool GetIsValid()
	{
		return m_isValid;
	}
	// �t���O�ݒ�
	void SetIsValid(bool _flag)
	{
		m_isValid = _flag;
	}

	float GetLife()
	{
		return m_life;
	}

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
	DirectX::GeometricPrimitive*	m_bullet;

	// �t���O
	bool m_isValid;
	// ��s����
	float m_life;
};