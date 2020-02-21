#pragma once

#include "StepTimer.h"

class GameScene
{
public: // ��{

	// �R���X�g���N�^
	GameScene() = default;
	// �f�X�g���N�^
	virtual ~GameScene() = default;

public: // �֐�

	// ������
	virtual void Initialize() = 0;
	// �X�V
	virtual void Update(DX::StepTimer const& _timer) = 0;
	// �`��
	virtual void Render() = 0;
	// �㏈��
	virtual void Finalize() = 0;
};