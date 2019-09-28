#pragma once

#include "CommonStates.h"
#include "DeviceResources.h"
#include "PrimitiveBatch.h"
#include "Effects.h"
#include "VertexTypes.h"
#include "SimpleMath.h"
#include "GameContext.h"

class GridFloor
{
public:

	GridFloor(float size, int divs);
	~GridFloor();

public:

	// �`��
	void draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj, DirectX::GXMVECTOR color = DirectX::Colors::Gray);

private:

	// Device Resources
	DX::DeviceResources* m_pDeviceResources;

	// �G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_pBasicEffect;

	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_pPrimitiveBatch;

	// �C���v�b�g���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;

	// �R�����X�e�[�g
	DirectX::CommonStates* m_pState;

	// ���̈�ӂ̃T�C�Y
	float m_size;

	// ������
	int m_divs;
};