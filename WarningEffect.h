#pragma once

#include <SimpleMath.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>

#include "DeviceResources.h"
#include "GameContext.h"
#include "WarningLine.h"
#include "WarningMessage.h"

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

	// ���C��
	std::unique_ptr<WarningLine>		m_pLine[2];
	// ���b�Z�[�W
	std::unique_ptr<WarningMessage>		m_pMessage;
	
	// ���C���e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_lineTexture;
	// ���b�Z�[�W�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_messageTexture;
	// �A�C�R���e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_iconTexture;

};