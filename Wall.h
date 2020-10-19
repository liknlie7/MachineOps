#pragma once

#include <Model.h>

#include "GameObject.h"
#include "Collision.h"

// ��
class Wall : public GameObject
{
public: // ��{

	// �R���X�g���N�^
	Wall() {};

	// �f�X�g���N�^
	~Wall() {};

public: // �֐�

	// ������
	void Initialize();
	
	// �X�V
	void Update()override {};
	
	// �`��
	void Render(const DirectX::SimpleMath::Matrix& _view) override;

private:

	// �ǂ̍쐬
	void CreateWall();

public: // �A�N�Z�T

	// �����蔻��̎擾
	Collision::Box GetCollider(int _num) const
	{
		return m_collider[_num];
	}

public: // �萔

	// �ǂ̈ʒu
	enum PLACE
	{
		TOP_RIGHT = 0,		// ��E��
		TOP_LEFT,			// �㍶��
		BOTTOM_RIGHT,		// ���E��
		BOTTOM_LEFT,		// ������
		LEFT_TOP,			// ���㑤
		LEFT_BOTTOM,		// ������
		RIGHT_TOP,			// �E�㑤
		RIGHT_BOTTOM,		// �E����

		ALL_PLACE,
	};

private: // �ϐ�

	// ���f��
	std::weak_ptr<DirectX::Model>				 m_pModel;

	// �R���C�_�[
	Collision::Box								 m_collider[ALL_PLACE];
};

