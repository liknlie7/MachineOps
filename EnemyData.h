#pragma once

// エネミーデータ
struct EnemyData
{
	int 		enemyType;			// エネミーの種類
	float		moveSpeed;			// 移動速度
	int			life;				// 体力
	int			shotType;			// 射撃タイプ
	float		collider;			// コライダー
};