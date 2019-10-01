#pragma once

#include <SimpleMath.h>
#include <GeometricPrimitive.h>
#include <Model.h>
#include <Effects.h>
#include <CommonStates.h>

#include "DeviceResources.h"
#include "Projection.h"
#include "GameObject.h"
#include "GameContext.h"

// �G
class Enemy : public GameObject
{
public: // ��{

	// �R���X�g���N�^
	Enemy();
	// �f�X�g���N�^
	~Enemy();

public: // �A�N�Z�T

	DirectX::SimpleMath::Vector3 Enemy::GetPos()
	{
		return m_pos;
	}

	DirectX::SimpleMath::Matrix Enemy::GetMat()
	{
		return m_mat;
	}

	// �ڐG����t���O�̎擾
	bool GetHitFlag()
	{
		return m_hitFlag;
	}
	// �ڐG����t���O�̐ݒ�
	void SetHitFlag(bool _hitFlag)
	{
		m_hitFlag = _hitFlag;
	}
	void DownLife(int _damege)
	{
		m_life -= _damege;
	}


public: // �֐�

	// ������
	void InitializeNormal(DirectX::SimpleMath::Vector3 _pos = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
	void InitializeShield(DirectX::SimpleMath::Vector3 _pos = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
	// �X�V
	void Update() override;
	void UpdateNormal(DirectX::SimpleMath::Vector3 _playerPos);
	void UpdateShield(DirectX::SimpleMath::Vector3 _playerPos);
	// �`��
	void Render(const DirectX::SimpleMath::Matrix& _view) override;
	// ��n��
	void Finalize();

	// �v���C���[��ǂ�������
	void ChasePlayer(DirectX::SimpleMath::Vector3 _playerPos);
	// �_��
	void Blink();

private: // �ϐ�

	// �G
	std::unique_ptr<DirectX::Model>	m_pEnemy;

	//�����蔻��p
	std::unique_ptr<DirectX::GeometricPrimitive> m_pDecisionArea;
	DirectX::SimpleMath::Vector3				 m_decisionAreaPos;
	DirectX::SimpleMath::Matrix					 m_decisionAreaMat;

	// ����
	float											m_speed;
	// �̗�
	int												m_life;
	// �q�b�g�t���O
	bool											m_hitFlag;
	// �_�Ŏ���
	int												m_blinkTime;
};