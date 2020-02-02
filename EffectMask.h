#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "Model.h"
#include "GameContext.h"
#include "File.h"
#include <list>

class EffectMask
{
private: // �萔

		 // �s�N�Z���V�F�[�_�[�ɓn���萔�o�b�t�@�̍\����
	struct cbChangesEveryFrame
	{
		FLOAT radius;
		FLOAT aspectRatio;
		DirectX::XMFLOAT2 dummy;
	};

public: // ��{

		// �R���X�g���N�^
	EffectMask();
	// �f�X�g���N�A��
	~EffectMask() {};

public: // �֐�

		// ������
	void Initialize(float _interval);
	// �X�V
	void Update(float _elapsedTime);
	// �`��
	void Render();

	// �I�[�v������֐�
	void Open();

	// �N���[�Y����֐�
	void Close();

	// �I�[�v�������`�F�b�N����֐�
	bool IsOpen();

	// �N���[�Y�����`�F�b�N����֐�
	bool IsClose();

	// �}�X�N�̐F�̐ݒ�֐�
	void SetColor(DirectX::FXMVECTOR color) { m_color = color; }

	// �I�[�v�����Ԃ��֐�(0�`1)
	float GetOpenRate() { return m_rate; }

public: // �ϐ�

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_cBuffer;

	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

private: // �ϐ�

		 // �I�[�v�����̓N���[�Y����܂ł̎���
	float m_interval;

	// ����(0�`1):0�̏ꍇ���Ă���
	float m_rate;

	// �I�[�v���t���O�itrue�̏ꍇ�I�[�v���j
	bool m_open;

	// �}�X�N�̐F
	DirectX::SimpleMath::Color m_color;

	// 2D�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_texture2D;

	// �萔�o�b�t�@
	cbChangesEveryFrame m_cbChangesEveryFrame;

	// �����_�[�^�[�Q�b�g�r���[
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;

	// �V�F�[�_�[���\�[�X�r���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_shaderResourceView;

};