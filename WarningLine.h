#pragma once

#include <SimpleMath.h>
#include <WICTextureLoader.h>
#include <SpriteBatch.h>

#include "GameContext.h"
#include "DeviceResources.h"
#include "Projection.h"

// �x�����C��
class WarningLine
{
public: // ��{

	// �R���X�g���N�^
	WarningLine();
	// �f�X�g���N�^
	~WarningLine() {};


private: // �萔

	// �G�t�F�N�g�\������
	static const float DISPLAY_TIME;

public: // �֐�

	// ������
	void Initialize();

	// �X�V
	void Update(float _elapsedTime);

	// �`��
	void Render();

private: // �ϐ�

	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_texture;

	// �\�����ԃJ�E���^
	float m_timer;

};

