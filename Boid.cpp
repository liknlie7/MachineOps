#include "pch.h"
#include "Boid.h"


// �R���X�g���N�^
Boid::Boid(const DirectX::SimpleMath::Vector3& _vector)
{
	// �����x������
	m_accel = DirectX::SimpleMath::Vector3::Zero;
	// ���x�𗐐��ŏ�����
	m_vel = DirectX::SimpleMath::Vector3(rand() % 2, 0, rand() % 2);
	// �ʒu������
	m_pos = _vector;
	// �ő呬�x
	m_maxSpeed = 1.5f;
	// �ő�����x
	m_maxForce = 0.5f;
}

// �R���X�g���N�^
Boid::Boid(const DirectX::SimpleMath::Vector3& _vector, const bool& _predCheck)
{
	m_predator = _predCheck;

	// �ߐH�҂����邩
	if (_predCheck == true)
	{
		// �ő呬�x�̑��
		m_maxSpeed = 1.5f;
		// �ő�����x�̑��
		m_maxForce = 0.5f;
		// �x�N�g���ɗ����l�̑��
		m_vel = DirectX::SimpleMath::Vector3(rand() % 2, 0, rand() % 2);
	}
	else
	{
		// �ő呬�x�̑��
		m_maxSpeed = 1.0f;
		// �ő�����x�̑��
		m_maxForce = 0.5f;
		// �x�N�g���ɗ����l�̑��
		m_vel = DirectX::SimpleMath::Vector3((rand() % 2) - 0.5f, 0, (rand() % 2) - 0.5f);
	}

	// �����x�̏�����
	m_accel = DirectX::SimpleMath::Vector3(0, 0, 0);
	// �ʒu�̏�����
	m_pos = DirectX::SimpleMath::Vector3(_vector);
}

// ����
void Boid::ApplyForce(const DirectX::SimpleMath::Vector3& _force)
{
	// �����x���グ��
	m_accel += _force;
}

// �����s��
// boid���݂��ɋ߂Â������Ȃ��悤�ɂ���
DirectX::SimpleMath::Vector3 Boid::Separation(std::vector<Boid> _boids)
{
	// Boid�̎���͈͂�ݒ肷��
	float desiredseparation = 3.0f;
	DirectX::SimpleMath::Vector3 steer = DirectX::SimpleMath::Vector3::Zero;
	int count = 0;

	// �eBoid���߂����Ă��邩
	for (int i = 0; i < _boids.size(); i++)
	{
		// Boid���m�̋����̌v�Z
		float distance = DirectX::SimpleMath::Vector3::Distance(m_pos, _boids[i].m_pos);

		// �߂����Ȃ痣���
		if ((distance > 0) && (distance < desiredseparation))
		{
			DirectX::SimpleMath::Vector3 diff = DirectX::SimpleMath::Vector3::Zero;
			diff = m_pos - _boids[i].m_pos;
			diff.Normalize();
			diff /= distance;
			steer += diff;
			count++;
		}

		// predator���m���߂��Ȃ痣���
		if ((distance > 0) && (distance < desiredseparation) && m_predator == true
			&& _boids[i].m_predator == true)
		{
			DirectX::SimpleMath::Vector3 pred2pred = DirectX::SimpleMath::Vector3::Zero;
			pred2pred = m_pos - _boids[i].m_pos;
			pred2pred.Normalize();
			pred2pred /= distance;
			steer += pred2pred;
			count++;
		}

		// ���݂�boid��predator�ł͂Ȃ��Ai��predator�ł���ꍇ����
		if ((distance > 0) && (distance < desiredseparation + 2.0f)
			&& _boids[i].m_predator == true)
		{
			DirectX::SimpleMath::Vector3 pred = DirectX::SimpleMath::Vector3::Zero;
			pred = DirectX::SimpleMath::operator-(m_pos, _boids[i].m_pos);
			pred *= 3.0f;
			steer += pred;
			count++;
		}
	}

	// �����x�Ɉʒu�̕��ς���
	if (count > 0)
		steer /= (float)count;

	if (Magnitude(steer) > 0)
	{
		steer.Normalize();
		steer *= m_maxSpeed;
		steer -= m_vel;
		steer = Limit(steer, m_maxForce);
	}
	return steer;
}

// ����s��
// �������boid�̕��ϑ��x���v�Z���āA����boid�̑��x�𑀍삷��
DirectX::SimpleMath::Vector3 Boid::Alignment(std::vector<Boid> _boids)
{
	// �ׂƂ̋���
	float neighbordist = 0.5f;
	DirectX::SimpleMath::Vector3 sum = DirectX::SimpleMath::Vector3::Zero;
	int count = 0;

	for (int i = 0; i < _boids.size(); i++)
	{
		float distance = DirectX::SimpleMath::Vector3::Distance(m_pos, _boids[i].m_pos);

		if ((distance > 0) && (distance < neighbordist))
		{
			sum += _boids[i].m_vel;
			count++;
		}
	}

	if (count > 0)
	{
		sum /= (float)count;
		sum.Normalize();
		sum *= m_maxSpeed;

		DirectX::SimpleMath::Vector3 steer;
		steer = sum - m_vel;

		steer = Limit(steer, m_maxForce);

		return steer;
	}
	else
	{
		DirectX::SimpleMath::Vector3 temp = DirectX::SimpleMath::Vector3::Zero;
		return temp;
	}
}

// �W��
// �߂���boid�̕��ψʒu��T���āA���̕����Ɉړ�������
DirectX::SimpleMath::Vector3 Boid::Cohesion(std::vector<Boid> _boids)
{
	float neighbordist = 0.5f;
	DirectX::SimpleMath::Vector3 sum = DirectX::SimpleMath::Vector3::Zero;
	int count = 0;
	for (int i = 0; i < _boids.size(); i++)
	{
		float distance = DirectX::SimpleMath::Vector3::Distance(m_pos, _boids[i].m_pos);
		if ((distance > 0) && (distance < neighbordist))
		{
			sum += _boids[i].m_pos;
			count++;
		}
	}
	if (count > 0)
	{
		sum /= count;
		return seek(sum);
	}
	else
	{
		DirectX::SimpleMath::Vector3 temp = DirectX::SimpleMath::Vector3::Zero;
		return temp;
	}
}

// maxSpeed�𐧌����ăx�N�g���𐳋K��
DirectX::SimpleMath::Vector3 Boid::seek(DirectX::SimpleMath::Vector3 _vector)
{
	DirectX::SimpleMath::Vector3 desired;
	// �ʒu����^�[�Q�b�g���w���x�N�g��
	desired -= _vector;
	// ���K��
	desired.Normalize();
	// �ő呬�x����Z
	desired *= m_maxSpeed;

	m_accel = desired - m_vel;
	m_accel = Limit(m_accel, m_maxForce);
	return m_accel;
}

// �X�V
void Boid::Update()
{
	// �����x��������
	m_accel *= 0.4f;

	// ���x�̍X�V
	m_vel += m_accel;

	// �������x
	m_vel = Limit(m_vel, m_maxSpeed);

	// �����x���Z�b�g
	m_accel *= 0.0f;
}

// ���s
void Boid::Run(std::vector<Boid> _boids)
{
	Flock(_boids);
	Update();
	//Borders();
}

// �Q��̍X�V
void Boid::Flock(std::vector<Boid> _boids)
{
	DirectX::SimpleMath::Vector3 sep = Separation(_boids);
	DirectX::SimpleMath::Vector3 ali = Alignment(_boids);
	DirectX::SimpleMath::Vector3 coh = Cohesion(_boids);

	sep *= 1.5f;
	ali *= 1.0f;
	coh *= 1.0f;

	ApplyForce(sep);
	ApplyForce(ali);
	ApplyForce(coh);
}

// �p�x�̌v�Z
float Boid::Angle(DirectX::SimpleMath::Vector3 _vector)
{
	float angle = (float)(atan2(_vector.x, -_vector.y) * 180 / DirectX::XM_PI);

	return angle;
}

float Boid::Magnitude(DirectX::SimpleMath::Vector3 _vector)
{
	return sqrt(_vector.x * _vector.x + _vector.y * _vector.y + _vector.z * _vector.z);
}

DirectX::SimpleMath::Vector3 Boid::Limit(DirectX::SimpleMath::Vector3 _vector, float _max)
{
	float size = Magnitude(_vector);

	if (size > _max)
	{
		return DirectX::SimpleMath::Vector3(_vector.x / size, _vector.y / size, _vector.z / size);
	}

	return _vector;
}
