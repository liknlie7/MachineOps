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
	Bullet(DirectX::SimpleMath::Vector3 _pos, float _angle, DirectX::SimpleMath::Vector3 _speed);
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

	bool GetIsValid()
	{
		return m_isValid;
	}

	void SetIsValid(bool _flag)
	{
		m_isValid = _flag;
	}

public: // 関数

	// 初期化
	void Initialize(DirectX::GeometricPrimitive* _type);
	// 更新
	void Update(float timer) override;
	// 描画
	void Render(const DirectX::SimpleMath::Matrix& _view) override;
	// 後処理
	void Finalize();

	// 衝突した時
	void OnCollision();

private: // 変数

	// 弾の形状
	DirectX::GeometricPrimitive*	m_bullet;

	// フラグ
	bool m_isValid;

};