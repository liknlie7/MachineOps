#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "MyEffect.h"
#include "Model.h"
#include "GameContext.h"
#include "File.h"
#include <list>

class EffectManager
{
public: // ��{

	EffectManager();
	~EffectManager() {};

public:
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Time;
	};

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	//void Create(const wchar_t* _name, int _count);
	//void Initialize(float _life, DirectX::SimpleMath::Vector3 _pos);
	//void InitializeNormal(float _life, DirectX::SimpleMath::Vector3 _pos);
	//void InitializeCorn(float _life, DirectX::SimpleMath::Vector3 _pos, DirectX::SimpleMath::Vector3 _dir);
	//void Update(DX::StepTimer _timer);
	//void Render();
	//void Lost();

	//void SetRenderState(DirectX::SimpleMath::Vector3 _camera, DirectX::SimpleMath::Matrix _view, DirectX::SimpleMath::Matrix _proj);
	//void Draw(DirectX::SimpleMath::Matrix _world, DirectX::SimpleMath::Matrix _view, DirectX::SimpleMath::Matrix _proj);

	//void RenderModel();

//private:
//	//MyEffect*					m_myEffect[10];
//	std::list<MyEffect*>		m_effectList;
//	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
//	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture2;
//
//
//	DX::StepTimer                           m_timer;
//
//
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_cBuffer;
//	std::unique_ptr<DirectX::CommonStates> m_states;
//
	// ���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	// �W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;
//
//	// �v���~�e�B�u�o�b�`
//	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
//	// ���̓��C�A�E�g
//	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
//	std::vector<DirectX::VertexPositionColorTexture>  m_vertex;
//
//	DirectX::SimpleMath::Vector3 m_centerPosition;
//
//	DirectX::SimpleMath::Matrix m_billboardTranslation;
//	DirectX::SimpleMath::Matrix m_view;
//	DirectX::SimpleMath::Matrix m_proj;
//
//	std::unique_ptr<DirectX::EffectFactory> m_fxFactory;
//	std::unique_ptr<DirectX::Model> m_model;
//
//
//	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_capture;
//	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	m_rtv;
//	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_srv;
//
//
	// TODO: �N���X����
	//�t�F�[�h-----------------------------------------------------------------------------------------------
public:
	// ������
	void InitializeMask(float _interval);
	// �X�V
	void UpdateEffectMask(float _elapsedTime);
	// �`��
	void DrawEffectMask();

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

private:
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

	// �s�N�Z���V�F�[�_�[�ɓn���萔�o�b�t�@�̍\����
	struct cbChangesEveryFrame
	{
		FLOAT radius;
		FLOAT aspectRatio;
		DirectX::XMFLOAT2 dummy;
	};

	// �萔�o�b�t�@
	cbChangesEveryFrame m_cbChangesEveryFrame;

	// �����_�[�^�[�Q�b�g�r���[
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;

	// �V�F�[�_�[���\�[�X�r���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_shaderResourceView;

};