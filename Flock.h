#pragma once

#include <vector>

#include "Boid.h"

// �Q��N���X
class Flock
{

public: // ��{

	// �R���X�g���N�^
	Flock() {}

public: // �A�N�Z�T

	// �T�C�Y�擾
	int GetSize() const
	{
		return m_flock.size();
	}

	// Boid�擾
	Boid GetBoid(int _i) const
	{
		return m_flock[_i];
	}

public: // �֐�

	// Boid�̒ǉ�
	void AddBoid(Boid _boid);

	// �X�V
	void flocking();

private: // �ϐ�

	// �Q��
	std::vector<Boid> m_flock;
};

