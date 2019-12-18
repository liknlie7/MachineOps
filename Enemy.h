#pragma once

#include <SimpleMath.h>
#include <GeometricPrimitive.h>
#include <Model.h>
#include <Effects.h>
#include <CommonStates.h>
#include <SpriteBatch.h>

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

	// 敵の種類
	enum EnemyType
	{
		NORMAL_TYPE= 1,
		SHIELD_TYPE,
		BOSS_TYPE,
	};

	// 射撃の種類
	enum ShotType
	{
		NORMAL_SHOT,			// 通常
		ALL_DIRECTION_SHOT,		// 全方位
		WINDER_SHOT,			// ワインダー
		WHORL_SHOT,				// うずまき
	};

public: // アクセサ

	// モデルの情報の取得
	DirectX::Model* GetModel()
	{
		return m_pEnemy.get();
	}

	// 座標取得
	DirectX::SimpleMath::Vector3 GetPos()
	{
		return m_pos;
	}

	// 弾の座標取得
	std::vector<DirectX::SimpleMath::Vector3> GetBulletPos()
	{
		std::vector<DirectX::SimpleMath::Vector3> bulletsPos;
		for (auto& numBullet : m_pBullets)
		{
			bulletsPos.push_back(numBullet->GetPos());
		}
		return bulletsPos;
	}

	// 接触判定フラグの取得
	bool GetIsValid()
	{
		return m_isValid;
	}

	// 接触判定フラグの設定
	void SetIsValid(bool _hitFlag)
	{
		m_isValid = _hitFlag;
	}

	// コライダーの取得
	Collision::Sphere GetCollider()
	{
		return m_collider;
	}

	// プレイヤーの位置の設定
	void SetPlayerPos(DirectX::SimpleMath::Vector3 _playerPos)
	{
		m_playerPos = _playerPos;
	}

	// 体力最大値の取得
	float GetMaxLife()
	{
		return m_maxLife;
	}
	// 現在の体力の取得
	float GetCurrentLife()
	{
		return m_life;
	}


public: // 関数

	// 初期化
	void Initialize(DirectX::SimpleMath::Vector3 _pos);
	// 更新
	void Update() override;
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
	// 弾が衝突した時
	void BulletOnCollision(int _number);
	// 弾が画面外に出たら
	void OutRangeBullet();


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
	int												m_enemyType;
	// 射撃タイプ
	int												m_shotType;
	// 射撃インターバル
	float											m_shotInterval;
	// 弾の回転
	float											m_shotRotate;
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
	float											m_maxLife;
	float											m_life;
	// ヒットフラグ
	bool											m_isValid;
	// 点滅時間
	int												m_blinkTime;


};