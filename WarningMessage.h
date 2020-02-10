#pragma once

#include <SimpleMath.h>
#include <WICTextureLoader.h>
#include <SpriteBatch.h>

#include "GameContext.h"

// �x�����b�Z�[�W
class WarningMessage
{
public: // ��{

	// �R���X�g���N�^
	WarningMessage();
	// �f�X�g���N�^
	~WarningMessage() {};

private: // �萔

	// �\������
	static const float DISPLAY_TIME;

	// �e�N�X�`����]��
	static const float ROTATION;

	// �e�N�X�`���g�嗦
	static const DirectX::SimpleMath::Vector2 MAGNIFICATION;

	// �t�F�[�h�X�s�[�h
	static const float FADE_SPEED;

public: // �֐�

	// ������
	void Initialize();

	// �X�V
	void Update(float _elapsedTime);

	// �`��
	void Render(ID3D11ShaderResourceView* _texture, DirectX::SimpleMath::Vector2 _pos);

private: // �ϐ�

	// �\�����ԃJ�E���^
	float m_timer;

	// �����x
	float m_alpha;

	// �t�F�[�h�^�C�v�ifalse�Ȃ�A�E�g�j
	bool m_fadeType;

};

