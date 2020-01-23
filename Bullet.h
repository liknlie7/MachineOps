#pragma once

#include <SimpleMath.h>
#include <GeometricPrimitive.h>

#include "Projection.h"
#include "GameContext.h"
#include "GameObject.h"

// 弾
class Bullet :public GameObject
{
public: // 基本

	// コンストラクタ
	Bullet(const DirectX::SimpleMath::Vector3& _pos, const float& _angle, const DirectX::SimpleMath::Vector3& _speed, const std::string& tag);
	// デストラクタ
	~Bullet() {}

public: // アクセサ

	// 座標取得
	DirectX::SimpleMath::Vector3 GetPos() const
	{
		return m_position;
	}
	// 座標設定
	void SetPos(const DirectX::SimpleMath::Vector3& _pos)
	{
		m_position = _pos;
	}

	// フラグ取得
	bool GetIsValid() const
	{
		return m_isValid;
	}
	// フラグ設定
	void SetIsValid(const bool& _flag)
	{
		m_isValid = _flag;
	}

	// 飛行時間の取得
	float GetLife() const
	{
		return m_life;
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

private: // 変数

	// 弾の形状
	DirectX::GeometricPrimitive*	m_bullet;

	// 回転
	DirectX::SimpleMath::Matrix		m_rotate;

	// フラグ
	bool m_isValid;

	// 飛行距離
	float m_life;
};