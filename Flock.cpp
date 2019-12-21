#include "pch.h"
#include "Flock.h"


// Boidの追加
void Flock::AddBoid(Boid _boid)
{
	m_flock.push_back(_boid);
}

// 更新
void Flock::flocking()
{
	// 個別更新
	for (int i = 0; i < m_flock.size(); i++)
		m_flock[i].Run(m_flock);
}
