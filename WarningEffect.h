#pragma once

#include <SimpleMath.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>

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

	// �������I�������
	bool IsEnd();

private: // �萔

	// �}�X�N�J���[
	static const DirectX::SimpleMath::Vector4 MASK_COLOR;

	// ���b�Z�[�W�ʒu
	static const DirectX::SimpleMath::Vector2 MESSAGE_POS;

	enum Texture
	{
		ICON = 0,		// �A�C�R��
		MESSAGE,		// ���b�Z�[�W
		LINE,			// ���C��
		MASK,			// �}�X�N�p

		ALL,
	};

private: // �ϐ�

	// ���C��
	std::unique_ptr<WarningLine>		m_pLine[2];
	// ���b�Z�[�W
	std::unique_ptr<WarningMessage>		m_pMessage;
	
	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_pTextures[Texture::ALL];

	// �}�X�N�p�J���[
	DirectX::SimpleMath::Vector4							m_maskColor;

	// �o�ߎ���
	float													m_time;
	// �\�����鎞��
	float													m_interval;
};