#pragma once

#include <SimpleMath.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>

#include "WarningLine.h"

class WarningEffect
{
public: // ��{

	// �R���X�g���N�^
	WarningEffect();
	// �f�X�g���N�^
	~WarningEffect() {};

public: // �֐�

	// ������
	void Initialize();
	// �X�V
	void Update(float _elapsedTime);
	// �`��
	void Render();

private: // �ϐ�

	std::unique_ptr<WarningLine>		m_pLine;
};

