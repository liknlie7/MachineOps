#pragma once

#include <SimpleMath.h>
#include <vector>

class Boid
{

public: // ��{

	// �R���X�g���N�^
	Boid() {}
	Boid(const DirectX::SimpleMath::Vector3& _vector);
	Boid(const DirectX::SimpleMath::Vector3& _vector, const bool& _predCheck);
	// �f�X�g���N�^
	~Boid() {}

public: // �A�N�Z�T

	DirectX::SimpleMath::Vector3 GetPos() const
	{
		return m_pos;
	}

public: // �֐�

	void ApplyForce(const DirectX::SimpleMath::Vector3& _force);

	DirectX::SimpleMath::Vector3 Separation(std::vector<Boid> _boids);
	DirectX::SimpleMath::Vector3 Alignment(std::vector<Boid> _boids);
	DirectX::SimpleMath::Vector3 Cohesion(std::vector<Boid> _boids);

	DirectX::SimpleMath::Vector3 seek(DirectX::SimpleMath::Vector3 _vector);
	void Run(std::vector<Boid> _boids);
	void Update();
	void Flock(std::vector<Boid> _boids);
	void Borders();
	float Angle(DirectX::SimpleMath::Vector3 _vector);
	float Magnitude(DirectX::SimpleMath::Vector3 _vector);
	DirectX::SimpleMath::Vector3 Limit(DirectX::SimpleMath::Vector3 _vector,float _max);

private: // �ϐ�

	bool							m_predator;
	DirectX::SimpleMath::Vector3	m_pos;
	DirectX::SimpleMath::Vector3	m_vel;
	DirectX::SimpleMath::Vector3	m_accel;
	float							m_maxSpeed;
	float							m_maxForce;
};

