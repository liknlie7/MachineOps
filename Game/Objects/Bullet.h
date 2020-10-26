#pragma once

#include <SimpleMath.h>
#include <GeometricPrimitive.h>

#include "GameObject.h"

// 弾
class Bullet :public GameObject
{
public: // 基本

	// コンストラクタ
	Bullet();
	
	// デストラクタ
	~Bullet() {}

public: // 関数

	// 初期化
	void Initialize() {};
	
	// 更新
	void Update() override;
	
	// 描画
	void Render(const DirectX::SimpleMath::Matrix& _view) override;
	
	// 後処理
	void Finalize() {};

public: // アクセサ

	// 角度の設定
	void SetAngle(const float _angle)
	{
		m_angle = _angle;
	}
	
	// 使用中かどうかの取得
	bool GetIsUsed() const
	{
		return m_isUsed;
	}

	// 使用中かどうかの設定
	void SetIsUsed(const bool _used)
	{
		m_isUsed = _used;
	}

	// 弾の形状を設定
	void SetBulletGeometry(DirectX::GeometricPrimitive* _bulletGeometry)
	{
		m_pBulletGeometry = _bulletGeometry;
	}

	// 速度の設定
	void SetSpeed(const float _speed)
	{
		m_speed = _speed;
	}

	// タグの設定
	void SetTag(const std::string& _tag)
	{
		m_tag = _tag;
	}

	// タグの取得
	const std::string& GetTag() const
	{
		return m_tag;
	}

private: // 定数

	// 弾の生存時間
	static const float BULLET_LIFE;

private: // 変数

	// 弾の形状
	DirectX::GeometricPrimitive*	m_pBulletGeometry;

	// 回転
	DirectX::SimpleMath::Matrix		m_rotate;

	// 角度
	float m_angle;

	// 飛行距離
	float m_life;

	// 弾の速度
	float m_speed;

	// タグ
	std::string m_tag;

	// 使用中か
	bool m_isUsed;
};