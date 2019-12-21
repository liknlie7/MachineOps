#pragma once

#include <SimpleMath.h>

// Boid�p
class Pvector
{

public: // ��{

	// �R���X�g���N�^
	Pvector() {}
	Pvector(const DirectX::SimpleMath::Vector3& _comp);

public: // �A�N�Z�T

	// �x�N�g���ݒ�
	void SetVector(const DirectX::SimpleMath::Vector3& _vector)
	{
		m_vector = _vector;
	}

public: // �֐�

	void AddScalar(float _scalar);

	void SubVector(Pvector _vector);
	Pvector SubTwoVector(Pvector _vector, Pvector _vector2);
	void SubScalar(float _scalar);

	void MulVector(Pvector _vector);
	void MulScalar(float _scalar);

	void DivVector(Pvector _vector);
	void DivScalar(float _scalar);

	void Limit(double _max);

	float DotProduct(Pvector _vector);
	void SetMagnitude(float _magni);
	float AngleBetween(Pvector _vector);

private: // �ϐ�

	DirectX::SimpleMath::Vector3 m_vector;

};

