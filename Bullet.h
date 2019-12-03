#pragma once

#include <SimpleMath.h>
#include <GeometricPrimitive.h>

#include "StepTimer.h"
#include "Projection.h"
#include "GameContext.h"
#include "GameObject.h"

#include "BulletFactory.h"

// 弾
class Bullet : public GameObject
{
public: // 基本

	// コンストラクタ
	Bullet() {};
	Bullet(DirectX::SimpleMath::Vector3 _pos, float _angle, DirectX::SimpleMath::Vector3 _speed);
	// デストラクタ
	~Bullet() {}

public: // アクセサ

	// 座標の取得
	DirectX::SimpleMath::Vector3 GetPosition()
	{
		return m_pos;
	}
	// 座標の設定
	void SetPosition(const DirectX::SimpleMath::Vector3& _pos)
	{
		m_pos = _pos;
	}

	// 角度の取得
	float GetAngle()
	{
		return m_angle;
	}
	// 角度の設定
	void SetAngle(float _angle)
	{
		m_angle = _angle;
	}

	// 衝突フラグの取得
	bool GetHitFlag()
	{
		return m_hitFlag;
	}
	// 衝突フラグの設定
	void SetHitFlag(bool _flag)
	{
		m_hitFlag = _flag;
	}

	// 使用中かどうかを取得する
	bool IsUsed() const
	{
		return m_used;
	}

	// 使用中かどうかを設定する
	void IsUsed(bool _used)
	{
		m_used = _used;
	}


public: // 関数

	// 初期化
	void Initialize(BulletFactory* _bulletFactory);
	// 更新
	void Update() override;
	// 描画
	void Render(const DirectX::SimpleMath::Matrix& _view) override;
	// 後処理
	void Finalize();

	// 衝突した時
	void OnCollision();

private: // 変数

	// 弾の形状
	DirectX::GeometricPrimitive*	m_bullet;

	// 角度
	float m_angle;

	// フラグ
	bool m_hitFlag;
	bool m_used;
};