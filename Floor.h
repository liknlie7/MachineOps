#pragma once

#include <Model.h>
#include <Effects.h>
#include <CommonStates.h>

#include "DeviceResources.h"
#include "SimpleMath.h"
#include "Projection.h"
#include "GameContext.h"
#include "Collision.h"

// ��
class Floor
{
public: // ��{

	// �R���X�g���N�^
	Floor() {}
	// �f�X�g���N�^
	~Floor() {}

public: // �A�N�Z�T

	// �O�p�`�̎擾
	Collision::Triangle GetTriangle(int _number) const
	{
		if (_number == 0)
			return Collision::Triangle(m_vector[0], m_vector[2], m_vector[1]);
		else
			return Collision::Triangle(m_vector[0], m_vector[3], m_vector[2]);
	}

public: // �֐�

	// ������
	void Initialize();
	// �`��
	void Render(DirectX::SimpleMath::Matrix _view);

public: // �萔

	// ����
	static const float AREA_WIDTH;
	// �c��
	static const float AREA_HEIGHT;

private: // �ϐ�

	// ���f��
	std::unique_ptr<DirectX::Model>	m_pModel;

	// �O�p�`
	//Collision::Triangle				m_tri[2];
	// ���_
	DirectX::SimpleMath::Vector3	m_vector[4];
};