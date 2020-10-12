#pragma once

#include <SimpleMath.h>
#include <mouse.h>
#include <SpriteBatch.h>

#include "DeviceResources.h"
#include "FollowCamera.h"
#include "GameContext.h"
#include "Projection.h"
#include "WICTextureLoader.h" 

class MouseCursor
{
public: // ��{

	// �R���X�g���N�^
	MouseCursor();
	// �f�X�g���N�^
	~MouseCursor() {}

public: // �A�N�Z�T

	DirectX::SimpleMath::Vector3 GetRayNear() const
	{
		return m_rayNear;
	}

	DirectX::SimpleMath::Vector3 GetRayFar() const
	{
		return m_rayFar;
	}

public: // �֐�

	// �X�V
	void Update();

	// �`��
	void Render();

private: // �ϐ�

	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_reticle;

	// �ʒu
	DirectX::SimpleMath::Vector3							m_pos;

	// Ray
	DirectX::SimpleMath::Vector3							m_rayNear;
	DirectX::SimpleMath::Vector3							m_rayFar;

	// �}�E�XState
	DirectX::SimpleMath::Vector3							m_state;
};

