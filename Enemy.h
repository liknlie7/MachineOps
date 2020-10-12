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
//#include "Bullet.h"
#include "GameObject.h"
#include "ResourceManager.h"
//#include "BulletManager.h"

// 敵
class Enemy : public GameObject
{
public: // 基本

	// コンストラクタ
	Enemy(const int _type);
	// デストラクタ
	~Enemy() {};

public:

	// 敵の種類
	enum EnemyType
	{
		NORMAL_ENEMY = 1,
		SHIELD_ENEMY,
		BOSS_ENEMY,
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
	//DirectX::Model* GetModel() const
	//{
	//	return m_pEnemy.get();
	//}

	// 座標取得
	DirectX::SimpleMath::Vector3 GetPos() const
	{
		return m_position;
	}

	// 弾の座標取得
	//std::vector<DirectX::SimpleMath::Vector3> GetBulletPos() const
	//{
	//	std::vector<DirectX::SimpleMath::Vector3> bulletsPos;
	//	for (auto& numBullet : m_pBullets)
	//	{
	//		bulletsPos.push_back(numBullet->GetPos());
	//	}
	//	return bulletsPos;
	//}

	// 接触判定フラグの取得
	bool GetIsValid() const
	{
		return m_isValid;
	}

	// 接触判定フラグの設定
	void SetIsValid(const bool& _hitFlag)
	{
		m_isValid = _hitFlag;
	}

	// コライダーの取得
	Collision::Sphere GetCollider() const
	{
		return m_collider;
	}

	// プレイヤーの位置の設定
	void SetPlayerPos(const DirectX::SimpleMath::Vector3& _playerPos)
	{
		m_playerPos = _playerPos;
	}

	// 体力の最大値取得
	float GetMaxLife() const
	{
		return m_maxLife;
	}
	// 体力の取得
	float GetLife() const
	{
		return m_life;
	}

	// 弾管理クラスのアドレスを設定
	//void SetBulletManager(BulletManager* _bullet)
	//{
	//	m_pBulletManager = _bullet;
	//}


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
	//// 弾が衝突した時
	//void BulletOnCollision(int _number);
	//// 弾が画面外に出たら
	//void OutRangeBullet();


private: // 定数

	// サイズ
	static const float SIZE;
	// ボスサイズ
	static const float BOSS_SIZE;

private: // 変数

	// モデル
	std::weak_ptr<DirectX::Model>					m_pEnemy;
	Collision::Sphere								m_collider;

	// 弾
	//std::unique_ptr<DirectX::GeometricPrimitive>	m_pBulletGeometric;
	//std::vector<std::unique_ptr<Bullet>>			m_pBullets;

	//// 弾管理用オブジェクト
	//BulletManager*									m_pBulletManager;

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