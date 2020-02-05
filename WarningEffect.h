#pragma once

#include <vector>
#include <SimpleMath.h>
#include <WICTextureLoader.h>

#include "DeviceResources.h"
#include "GameContext.h"
#include "File.h"



// �x�����C��
class WarningEffect
{
private: // �萔

	// �s�N�Z���V�F�[�_�[�ɓn���萔�o�b�t�@�̍\����
	struct cbChangesEveryFrame
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 dummy;
	};

public: // ��{

	// �R���X�g���N�^
	WarningEffect();
	// �f�X�g���N�^
	~WarningEffect() {};

public: // �֐�

	// ������
	void Initialize();
	// �X�V
	void Update();
	
public: // �ϐ�

	static const std::vector<D3D11_INPUT_ELEMENT_DESC>		INPUT_LAYOUT;

	Microsoft::WRL::ComPtr<ID3D11Buffer>					m_cBuffer;

	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader>				m_pixelShader;

private: // �ϐ�

	// �����_�[�^�[�Q�b�g�r���[
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;

	// �V�F�[�_�[���\�[�X�r���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_shaderResourceView;

	// �萔�o�b�t�@
	cbChangesEveryFrame m_cbChangesEveryFrame;

	// 2D�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	// �I�[�v�����̓N���[�Y����܂ł̎���
	float m_interval;

	// ����(0�`1):0�̏ꍇ���Ă���
	float m_rate;

	// �I�[�v���t���O�itrue�̏ꍇ�I�[�v���j
	bool m_open;

	// �}�X�N�̐F
	DirectX::SimpleMath::Color m_color;
};

