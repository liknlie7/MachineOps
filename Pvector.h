#pragma once

#include <SimpleMath.h>

// Boid用
class Pvector
{

public: // 基本

	// コンストラクタ
	Pvector() {}
	Pvector(const DirectX::SimpleMath::Vector3& _comp);

public: // アクセサ

	// ベクトル設定
	void SetVector(const DirectX::SimpleMath::Vector3& _vector)
	{
		m_vector = _vector;
	}

public: // 関数

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

private: // 変数

	DirectX::SimpleMath::Vector3 m_vector;

};

