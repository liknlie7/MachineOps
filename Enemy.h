#pragma once

#include <SimpleMath.h>
#include <Model.h>

#include "GameObject.h"
#include "BulletManager.h"
#include "GameObject.h"
#include "EnemyData.h"
#include "Collision.h"

// エネミー
class Enemy : public GameObject
{
public: // 基本

	// コンストラクタ
	Enemy(const EnemyData& _enemyData);

	// デストラクタ
	~Enemy() {};

public: // 関数

	// 初期化
	void Initialize(const DirectX::SimpleMath::Vector3& _pos);
	
	// 更新
	void Update() override;
	
	// 描画
	void Render(const DirectX::SimpleMath::Matrix& _view) override;
	
	// 後始末
	void Finalize() {};

	// 衝突した時
	void OnCollision();

private: // 関数

	// プレイヤーを追いかける
	void ChasePlayer(const DirectX::SimpleMath::Vector3& _playerPos);

	// 点滅
	void Blink();

	// 射撃パターンの切り替え
	void ChangeShotPattern();

	// プレイヤーの方向に向ける
	void TurnToDirectionPlayer();

	// 弾を撃つ
	void Shot();

public: // アクセサ

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
	void SetBulletManager(BulletManager* _bullet)
	{
		m_pBulletManager = _bullet;
	}

public: // 定数

	// エネミーの種類
	enum EnemyType
	{
		NORMAL_ENEMY = 1,	// 通常
		SHIELD_ENEMY,		// 盾
		BOSS_ENEMY,			// ボス
	};

private: // 定数

	// 射撃の種類
	enum ShotType
	{
		NORMAL_SHOT = 1,		// 通常
		ALL_DIRECTION_SHOT,		// 全方位
		WHORL_SHOT,				// うずまき
	};

	// サイズ
	static const float SIZE;

	// ボスサイズ
	static const float BOSS_SIZE;

	// 弾を撃つ間隔
	static const float NORMAL_SHOT_INTERVEL;
	static const float ALL_DIRECTION_SHOT_INTERVEL;
	static const float WHORL_SHOT_INTERVEL;

	// 点滅間隔
	static const float BLINK_TIME;

	// 弾の速度
	static const float BULLET_SPEED;

private: // 変数

	// モデル
	std::weak_ptr<DirectX::Model>					m_pEnemy;
	Collision::Sphere								m_collider;

	// 弾管理用オブジェクト
	BulletManager*									m_pBulletManager;

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
	float											m_moveSpeed;
	
	// エネミー機の角度
	float											m_enemyAngle;
	
	// Way数
	int												m_shotWayNum;
	
	// 弾の端の角度
	float											m_bulletEndAngle;
	
	// 弾の角度の間隔
	float											m_bulletChangeAngle;
	
	// 体力
	float											m_life;
	float											m_maxLife;
		
	// ヒットフラグ
	bool											m_hitFlag;

	// 点滅時間
	int												m_blinkTime;
};