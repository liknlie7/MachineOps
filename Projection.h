#pragma once

#include "SimpleMath.h"

// �v���W�F�N�V����
class Projection final
{
public: // ��{

	// �R���X�g���N�^
	Projection() = default;

	// �f�X�g���N�^
	~Projection() = default;

public: // �֐�

	// �s��̎擾
	const DirectX::SimpleMath::Matrix& GetMatrix() const;

	// ����̐ݒ�
	void SetPerspectiveFieldOfView(float _fov, float _aspectRatio, float _nearPlane, float _farPlane);

private: // �ϐ�

	// �s��
	DirectX::SimpleMath::Matrix m_matrix;
};

// �s��̎擾
inline const DirectX::SimpleMath::Matrix& Projection::GetMatrix() const
{
	return m_matrix;
}

// ����̐ݒ�
inline void Projection::SetPerspectiveFieldOfView(float _fov, float _aspectRatio, float _nearPlane, float _farPlane)
{
	m_matrix = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(_fov, _aspectRatio, _nearPlane, _farPlane);
}