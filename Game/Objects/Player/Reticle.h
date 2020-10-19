#pragma once

#include <SimpleMath.h>
#include <SpriteBatch.h>

#include "WICTextureLoader.h" 

// �Ə��N���X
class Reticle
{
public: // ��{

	// �R���X�g���N�^
	Reticle();

	// �f�X�g���N�^
	~Reticle() {}

public: // �֐�

	// �X�V
	void Update();

	// �`��
	void Render();

public: // �A�N�Z�T

	// Ray�̎n�_�擾
	DirectX::SimpleMath::Vector3 GetRayNear() const
	{
		return m_rayNear;
	}

	// Ray�̏I�_�擾
	DirectX::SimpleMath::Vector3 GetRayFar() const
	{
		return m_rayFar;
	}

private: // �萔

	// �Ə��傫��
	static const DirectX::SimpleMath::Vector2 RETICLE_SCALE;

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