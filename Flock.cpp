#include "pch.h"
#include "Flock.h"


// Boid�̒ǉ�
void Flock::AddBoid(Boid _boid)
{
	m_flock.push_back(_boid);
}

// �X�V
void Flock::flocking()
{
	// �ʍX�V
	for (int i = 0; i < m_flock.size(); i++)
		m_flock[i].Run(m_flock);
}
