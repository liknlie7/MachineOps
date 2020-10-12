#pragma once

#include <Model.h>
#include <SimpleMath.h>
#include <Effects.h>

#include "DeviceResources.h"
#include "GameObject.h"
#include "GameContext.h"
#include "Projection.h"
#include "Collision.h"

#include <GeometricPrimitive.h>

// ��
class Wall : public GameObject
{

public: // ��{

	// �R���X�g���N�^
	Wall();
	// �f�X�g���N�^
	~Wall() {};

public: // �A�N�Z�T

	// �����蔻��̎擾
	Collision::Box GetCollider(int _num) const
	{
		return m_collider[_num];
	}

public: // �֐�

	// ������
	void Initialize();
	// �X�V
	void Update()override {};
	// �`��
	void Render(const DirectX::SimpleMath::Matrix& _view) override;

public: // �萔

	enum PLACE
	{
		TOP_RIGHT,		// ��E��
		TOP_LEFT,		// �㍶��
		BOTTOM_RIGHT,	// ���E��
		BOTTOM_LEFT,	// ������
		LEFT_TOP,		// ���㑤
		LEFT_BOTTOM,	// ������
		RIGHT_TOP,		// �E�㑤
		RIGHT_BOTTOM,	// �E����

		ALL_PLACE,
	};

private: // �ϐ�

	// ���f��
	std::unique_ptr<DirectX::Model>	m_pModel;

	// �R���C�_�[
	Collision::Box					m_collider[ALL_PLACE];

	std::unique_ptr<DirectX::GeometricPrimitive> m_test;
};

