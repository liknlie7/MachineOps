#include "pch.h"
#include "Boid.h"


// コンストラクタ
Boid::Boid(const DirectX::SimpleMath::Vector3& _vector)
{
	// 加速度初期化
	m_accel = DirectX::SimpleMath::Vector3::Zero;
	// 速度を乱数で初期化
	m_vel = DirectX::SimpleMath::Vector3(rand() % 2, 0, rand() % 2);
	// 位置初期化
	m_pos = _vector;
	// 最大速度
	m_maxSpeed = 1.5f;
	// 最大加速度
	m_maxForce = 0.5f;
}

// コンストラクタ
Boid::Boid(const DirectX::SimpleMath::Vector3& _vector, const bool& _predCheck)
{
	m_predator = _predCheck;

	// 捕食者がいるか
	if (_predCheck == true)
	{
		// 最大速度の代入
		m_maxSpeed = 1.5f;
		// 最大加速度の代入
		m_maxForce = 0.5f;
		// ベクトルに乱数値の代入
		m_vel = DirectX::SimpleMath::Vector3(rand() % 2, 0, rand() % 2);
	}
	else
	{
		// 最大速度の代入
		m_maxSpeed = 1.0f;
		// 最大加速度の代入
		m_maxForce = 0.5f;
		// ベクトルに乱数値の代入
		m_vel = DirectX::SimpleMath::Vector3((rand() % 2) - 0.5f, 0, (rand() % 2) - 0.5f);
	}

	// 加速度の初期化
	m_accel = DirectX::SimpleMath::Vector3(0, 0, 0);
	// 位置の初期化
	m_pos = DirectX::SimpleMath::Vector3(_vector);
}

// 加速
void Boid::ApplyForce(const DirectX::SimpleMath::Vector3& _force)
{
	// 加速度を上げる
	m_accel += _force;
}

// 分離行動
// boidが互いに近づきすぎないようにする
DirectX::SimpleMath::Vector3 Boid::Separation(std::vector<Boid> _boids)
{
	// Boidの視野範囲を設定する
	float desiredseparation = 3.0f;
	DirectX::SimpleMath::Vector3 steer = DirectX::SimpleMath::Vector3::Zero;
	int count = 0;

	// 各Boidが近すぎているか
	for (int i = 0; i < _boids.size(); i++)
	{
		// Boid同士の距離の計算
		float distance = DirectX::SimpleMath::Vector3::Distance(m_pos, _boids[i].m_pos);

		// 近すぎなら離れる
		if ((distance > 0) && (distance < desiredseparation))
		{
			DirectX::SimpleMath::Vector3 diff = DirectX::SimpleMath::Vector3::Zero;
			diff = m_pos - _boids[i].m_pos;
			diff.Normalize();
			diff /= distance;
			steer += diff;
			count++;
		}

		// predator同士が近いなら離れる
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

		// 現在のboidがpredatorではない、iがpredatorである場合分離
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

	// 加速度に位置の平均を代入
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

// 整列行動
// 視野内のboidの平均速度を計算して、他のboidの速度を操作する
DirectX::SimpleMath::Vector3 Boid::Alignment(std::vector<Boid> _boids)
{
	// 隣との距離
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

// 集合
// 近くのboidの平均位置を探して、その方向に移動させる
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

// maxSpeedを制限してベクトルを正規化
DirectX::SimpleMath::Vector3 Boid::seek(DirectX::SimpleMath::Vector3 _vector)
{
	DirectX::SimpleMath::Vector3 desired;
	// 位置からターゲットを指すベクトル
	desired -= _vector;
	// 正規化
	desired.Normalize();
	// 最大速度を乗算
	desired *= m_maxSpeed;

	m_accel = desired - m_vel;
	m_accel = Limit(m_accel, m_maxForce);
	return m_accel;
}

// 更新
void Boid::Update()
{
	// 加速度を下げる
	m_accel *= 0.4f;

	// 速度の更新
	m_vel += m_accel;

	// 制限速度
	m_vel = Limit(m_vel, m_maxSpeed);

	// 加速度リセット
	m_accel *= 0.0f;
}

// 実行
void Boid::Run(std::vector<Boid> _boids)
{
	Flock(_boids);
	Update();
	//Borders();
}

// 群れの更新
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

// 角度の計算
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
