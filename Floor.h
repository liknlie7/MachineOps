#pragma once

#include <Model.h>
#include <SimpleMath.h>

#include "Collision.h"
#include "GameObject.h"

// ��
class Floor : public GameObject
{
public: // ��{

	// �R���X�g���N�^
	Floor() {};

	// �f�X�g���N�^
	~Floor() {}

public: // �֐�

	// ������
	void Initialize();

	// �X�V
	void Update() override {};

	// �`��
	void Render(const DirectX::SimpleMath::Matrix& _view) override;

public: // �A�N�Z�T

	// �O�p�`�̎擾
	Collision::Triangle GetTriangle(int _number) const
	{
		if (_number == 0)
			return Collision::Triangle(m_vector[0], m_vector[2], m_vector[1]);
		else
			return Collision::Triangle(m_vector[0], m_vector[3], m_vector[2]);
	}


public: // �萔

	// ����
	static const float AREA_WIDTH;
	
	// �c��
	static const float AREA_HEIGHT;

private: // �ϐ�

	// ���f��
	std::weak_ptr<DirectX::Model>	m_pModel;

	// ���_
	DirectX::SimpleMath::Vector3	m_vector[4];
};