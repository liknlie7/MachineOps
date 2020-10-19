#pragma once

#include <SimpleMath.h>
#include <WICTextureLoader.h>
#include <SpriteBatch.h>

// �x�����C��
class WarningLine
{
public: // ��{

	// �R���X�g���N�^
	WarningLine();
	
	// �f�X�g���N�^
	~WarningLine() {};

public: // �֐�

	// ������
	void Initialize(DirectX::SimpleMath::Vector2 _pos, bool _dir);

	// �X�V
	void Update(float _elapsedTime);

	// �`��
	void Render(ID3D11ShaderResourceView* _texture);

private: // �萔

	// �\������
	static const float DISPLAY_TIME;

	// �e�N�X�`����]��
	static const float ROTATION;

	// �e�N�X�`���g�嗦
	static const DirectX::SimpleMath::Vector2 MAGNIFICATION;

	// ���x
	static const float SPEED;

private: // �ϐ�

	// �\�����ԃJ�E���^
	float m_timer;

	// ���W
	DirectX::SimpleMath::Vector2 m_pos;

	// �����i�������Ȃ�false
	bool m_dir;
};

