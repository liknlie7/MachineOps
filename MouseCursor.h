#pragma once

#include <SimpleMath.h>
#include <mouse.h>
#include <SpriteBatch.h>

#include "DeviceResources.h"
#include "FollowCamera.h"
#include "GameContext.h"
#include "Projection.h"
#include "WICTextureLoader.h" 
#include "GameObject.h"

class MouseCursor : public GameObject
{
public: // ��{

	// �R���X�g���N�^
	MouseCursor(const std::string& _tag);
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
	void Update() override;

	// �`��
	void Render(const DirectX::SimpleMath::Matrix& _view) override;

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

