#pragma once

#include <SimpleMath.h>
#include <GeometricPrimitive.h>

#include "DeviceResources.h"
#include "Projection.h"
#include "GameContext.h"
#include "GameObject.h"

// 弾
class Bullet :public GameObject
{
public: // 基本

	// コンストラクタ
	Bullet(const DirectX::SimpleMath::Vector3& _pos, const DirectX::SimpleMath::Vector3& _vel, const float& _angle);
	// デストラクタ
	~Bullet() {}

public: // アクセサ

	// 角度の設定
	void SetAngle(const float _angle)
	{
		m_angle = _angle;
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

	// 使用中かどうかの取得
	bool GetIsUsed()
	{
		return m_used;
	}

	// 使用中かどうかの設定
	void SetIsUsed(bool _used)
	{
		m_used = _used;
	}

	//// 弾の形状を設定
	//void SetBulletType(DirectX::GeometricPrimitive* _bulletType)
	//{
	//	m_bullet = _bulletType;
	//}

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
	//DirectX::GeometricPrimitive*	m_bullet;

	// 回転
	DirectX::SimpleMath::Matrix		m_rotate;

	// 角度
	float m_angle;

	// フラグ
	bool m_isValid;

	// 飛行距離
	float m_life;

	// 使用中か
	bool m_used;
};