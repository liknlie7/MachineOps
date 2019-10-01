#pragma once

#include <SimpleMath.h>
#include <GeometricPrimitive.h>

#include "StepTimer.h"
#include "Projection.h"
#include "GameContext.h"
#include "GameObject.h"

// 弾
class Bullet :public GameObject
{
public: // 基本

	// コンストラクタ
	Bullet(DirectX::SimpleMath::Vector3 _pos, float _angle);
	// デストラクタ
	~Bullet() {}

public: // アクセサ

	// 座標取得
	DirectX::SimpleMath::Vector3 GetPos()
	{
		return m_pos;
	}

	// 座標設定
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
	// 更新
	void Update() override;
	// 描画
	void Render(const DirectX::SimpleMath::Matrix& _view) override;
	// 後処理
	void Finalize();

public: // 定数

	// 弾スピード
	static const DirectX::SimpleMath::Vector3 SPEED;

private: // 変数

	// 弾の形状
	DirectX::GeometricPrimitive*	m_bullet;

	// フラグ
	bool m_hitFlag;

};