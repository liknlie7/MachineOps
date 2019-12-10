#pragma once

#include <SimpleMath.h>
#include <GeometricPrimitive.h>

#include "StepTimer.h"
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

	bool GetIsValid()
	{
		return m_isValid;
	}

	void SetIsValid(bool _flag)
	{
		m_isValid = _flag;
	}

public: // �֐�

	// ������
	void Initialize(DirectX::GeometricPrimitive* _type);
	// �X�V
	void Update(float timer) override;
	// �`��
	void Render(const DirectX::SimpleMath::Matrix& _view) override;
	// �㏈��
	void Finalize();

	// �Փ˂�����
	void OnCollision();

private: // �ϐ�

	// �e�̌`��
	DirectX::GeometricPrimitive*	m_bullet;

	// �t���O
	bool m_isValid;

};