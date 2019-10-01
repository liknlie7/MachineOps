#pragma once

#include <SimpleMath.h>
#include <GeometricPrimitive.h>

#include "StepTimer.h"
#include "Projection.h"
#include "GameContext.h"

// 弾
class Bullet
{
public: // 基本

	// コンストラクタ
	Bullet(DirectX::SimpleMath::Vector3 _pos, float _angle);
	// デストラクタ
	~Bullet() {}

public: // アクセサ

	// 座標を取得する
	DirectX::SimpleMath::Vector3 GetPos()
	{
		return m_pos;
	}

	// 座標を設定する
	void SetPos(const DirectX::SimpleMath::Vector3& _pos)
	{
		m_pos = _pos;
	}

	bool GetHitFlag()
	{
		return m_hitFlag;
	}
	void SetHitFlag(bool _hitFlag)
	{
		m_hitFlag = _hitFlag;
	}

public: // 関数

	// 初期化
	void Initialize(DirectX::GeometricPrimitive* _type);
	// 更新する
	void Update();
	// 描画する
	void Render(DirectX::SimpleMath::Matrix _view);
	// 後処理
	void Finalize();

public: // 定数

	// 弾スピード
	static const DirectX::SimpleMath::Vector3 SPEED;

private: // 変数

	// 弾
	DirectX::GeometricPrimitive*	m_bullet;
	// 位置
	DirectX::SimpleMath::Vector3	m_pos;
	// 行列
	DirectX::SimpleMath::Matrix		m_matrix;
	// 速度
	DirectX::SimpleMath::Vector3	m_vel;

	// フラグ
	bool m_hitFlag;

};