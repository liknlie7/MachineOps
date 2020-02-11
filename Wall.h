#pragma once

#include <Model.h>
#include <SimpleMath.h>
#include <Effects.h>

#include "DeviceResources.h"
#include "GameObject.h"
#include "GameContext.h"
#include "Projection.h"

// ��
class Wall : public GameObject
{
public: // ��{

	// �R���X�g���N�^
	Wall(const std::string& _tag);
	// �f�X�g���N�^
	~Wall() {};

public: // �֐�

	// ������
	void Initialize();
	// �X�V
	void Update() override;
	// �`��
	void Render(const DirectX::SimpleMath::Matrix& _view) override;

private: // �ϐ�

	// ���f��
	std::unique_ptr<DirectX::Model>	m_pModel;
};

