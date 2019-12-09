#pragma once

#include <SimpleMath.h>
#include <GeometricPrimitive.h>
#include <Model.h>
#include <Effects.h>
#include <CommonStates.h>

#include "DeviceResources.h"
#include "Projection.h"
#include "Collision.h"
#include "GameObject.h"
#include "GameContext.h"
#include "Bullet.h"

// 敵
class Enemy : public GameObject
{
public: // 基本

	// コンストラクタ
	Enemy(int _type);
	// デストラクタ
	~Enemy();

public:

	enum Type
	{
		Normal = 1,
		Shield,
	};

public: // アクセサ

	DirectX::Model* GetModel()
	{
		return m_pEnemy.get();
	}

	// 座標取得
	DirectX::SimpleMath::Vector3 GetPos()
	{
		return m_pos;
	}

	// 接触判定フラグの取得
	bool GetHitFlag()
	{
		return m_hitFlag;
	}

	// 接触判定フラグの設定
	void SetHitFlag(bool _hitFlag)
	{
		m_hitFlag = _hitFlag;
	}

	Collision::Sphere GetCollider()
	{
		return m_collider;
	}

	void SetPlayerPos(DirectX::SimpleMath::Vector3 _playerPos)
	{
		m_playerPos = _playerPos;
	}

public: // 関数

	// 初期化
	void Initialize(DirectX::SimpleMath::Vector3 _pos);
	// 更新
	void Update(DX::StepTimer const& timer) override;
	// 描画
	void Render(const DirectX::SimpleMath::Matrix& _view) override;
	// 後始末
	void Finalize();

	// プレイヤーを追いかける
	void ChasePlayer(DirectX::SimpleMath::Vector3 _playerPos);
	// 点滅
	void Blink();
	// 弾の作成
	void CreateBullet();

	// 衝突した時
	void OnCollision();


private: // 変数

	// モデル
	std::unique_ptr<DirectX::Model>					m_pEnemy;
	Collision::Sphere								m_collider;

	// 弾
	std::unique_ptr<DirectX::GeometricPrimitive>	m_pBulletGeometric;
	std::vector<std::unique_ptr<Bullet>>			m_pBullets;

	// プレイヤーの位置
	DirectX::SimpleMath::Vector3					m_playerPos;

	// タイプ
	int												m_type;
	// 速さ
	float											m_speed;
	// 敵機の角度
	float											m_enemyAngle;
	// Way数
	int												m_wayNum;
	// 弾の端の角度
	float											m_bulletEndAngle;
	// 弾の角度の間隔
	float											m_changeAngle;
	// 体力
	int												m_life;
	// ヒットフラグ
	bool											m_hitFlag;
	// 点滅時間
	int												m_blinkTime;


};