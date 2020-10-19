#pragma once

#include <SimpleMath.h>
#include <Keyboard.h>
#include <Mouse.h>
#include <Model.h>

#include "../../Manager/Collision.h"
#include "../../Manager/Bulletmanager.h"
#include "../../Objects/GameObject.h"
#include "../../Sound/Adx2Le.h"

// プレイヤークラス
class Player : public GameObject
{
public: // 基本

	// コンストラクタ
	Player();

	// デストラクタ
	~Player();

public: // 関数

	// 初期化
	void Initialize();

	// 更新
	void Update() override;

	// 描画
	void Render(const DirectX::SimpleMath::Matrix& _view) override;

	// 後始末
	void Finalize() {};

	// 衝突
	void OnCollision();

private: //関数

	// 移動
	void Move();

	// 弾を撃つ
	void Shot();

public: // アクセサ

	// マウス座標の設定
	void SetMousePos(const DirectX::SimpleMath::Vector3& _mousePos)
	{
		m_mousePos = _mousePos;
	}

	// 当たり判定の取得
	Collision::Sphere GetCollider() const
	{
		return m_collider;
	}

	// 弾管理クラスのアドレスを設定
	void SetBulletManager(BulletManager* _bullet)
	{
		m_pBulletManager = _bullet;
	}

private: // 定数

	// 移動制限範囲
	static const DirectX::SimpleMath::Vector3 RANGE_MIN;
	static const DirectX::SimpleMath::Vector3 RANGE_MAX;

	// 弾の速度
	static const float BULLET_SPEED;

	// 弾を撃つ間隔
	static const float SHOT_INTERVAL;

	// プレイヤー移動速度
	static const float MOVE_SPEED;

	// プレイヤー移動速度(シフト押し)
	static const float MOVE_SLOW_SPEED;

private: // 変数

	// キーボード
	std::unique_ptr<DirectX::Keyboard>			 m_keyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboardTracker;

	// マウストラッカー
	DirectX::Mouse::ButtonStateTracker			 m_mouseTracker;

	// サウンド
	std::weak_ptr<Adx2Le>						 m_pSound;

	// プレイヤー
	std::weak_ptr<DirectX::Model>				 m_pPlayer;
	Collision::Sphere							 m_collider;

	// 弾管理のオブジェクト
	BulletManager*								 m_pBulletManager;

	// 向き
	DirectX::SimpleMath::Vector3				 m_dir;

	// マウス座標
	DirectX::SimpleMath::Vector3				 m_mousePos;

	// 角度
	float										 m_angle;

	// インターバル
	float										 m_shotInterval;

	// ヒットフラグ
	bool										 m_hitFlag;

	// Shiftボタンフラグ
	bool										 m_isShiftDown;
};