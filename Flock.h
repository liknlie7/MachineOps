#pragma once

#include <vector>

#include "Boid.h"

// 群れクラス
class Flock
{

public: // 基本

	// コンストラクタ
	Flock() {}

public: // アクセサ

	// サイズ取得
	int GetSize() const
	{
		return m_flock.size();
	}

	// Boid取得
	Boid GetBoid(int _i) const
	{
		return m_flock[_i];
	}

public: // 関数

	// Boidの追加
	void AddBoid(Boid _boid);

	// 更新
	void flocking();

private: // 変数

	// 群れ
	std::vector<Boid> m_flock;
};

