#pragma once

#include <SimpleMath.h>
#include <GeometricPrimitive.h>

#include "StepTimer.h"
#include "Projection.h"
#include "GameContext.h"

// �e
class Bullet
{
public: // ��{

	// �R���X�g���N�^
	Bullet(DirectX::SimpleMath::Vector3 _pos, float _angle);
	// �f�X�g���N�^
	~Bullet() {}

public: // �A�N�Z�T

	// ���W���擾����
	DirectX::SimpleMath::Vector3 GetPos()
	{
		return m_pos;
	}

	// ���W��ݒ肷��
	void SetPos(const DirectX::SimpleMath::Vector3& _pos)
	{
		m_pos = _pos;
	}

	bool GetHitFlag()
	{
		return m_hitFlag;
	}
	void SetHitFlag(bool _hitFlag)
	{
		m_hitFlag = _hitFlag;
	}

public: // �֐�

	// ������
	void Initialize(DirectX::GeometricPrimitive* _type);
	// �X�V����
	void Update();
	// �`�悷��
	void Render(DirectX::SimpleMath::Matrix _view);
	// �㏈��
	void Finalize();

public: // �萔

	// �e�X�s�[�h
	static const DirectX::SimpleMath::Vector3 SPEED;

private: // �ϐ�

	// �e
	DirectX::GeometricPrimitive*	m_bullet;
	// �ʒu
	DirectX::SimpleMath::Vector3	m_pos;
	// �s��
	DirectX::SimpleMath::Matrix		m_matrix;
	// ���x
	DirectX::SimpleMath::Vector3	m_vel;

	// �t���O
	bool m_hitFlag;

};