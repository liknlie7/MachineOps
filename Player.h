#pragma once

#include <SimpleMath.h>
#include <Keyboard.h>
#include <Mouse.h>
#include <GeometricPrimitive.h>
#include <Model.h>
#include <Effects.h>
#include <CommonStates.h>

#include "DeviceResources.h"
#include "Projection.h"
#include "Collision.h"
#include "GameContext.h"
#include "GameObject.h"
#include "Weapon.h"
#include "Sound.h"

class Bullet;
class Weapon;

class Player : public GameObject
{
private:

	enum STATE
	{
		STATE_NORMAL,
		STATE_HIT,
		STATE_DEAD,
	};

public: // 基本

	// コンストラクタ
	Player(const std::string& _tag);
	// デストラクタ
	~Player();

public: // アクセサ

	// 座標の取得
	DirectX::SimpleMath::Vector3 Player::GetPos() const
	{
		return m_position;
	}

	// マウス座標の設定
	void SetMousePos(const DirectX::SimpleMath::Vector3& _mousePos)
	{
		m_mousePos = _mousePos;
	}

	// 弾の座標取得
	std::vector<DirectX::SimpleMath::Vector3> GetBulletPos() const
	{
		return m_pWeapon->GetBulletPos();
	}

	// 接触判定フラグの取得
	bool GetHitFlag() const
	{
		return m_hitFlag;
	}
	// 接触判定フラグの設定
	void SetHitFlag(const bool& _hitFlag)
	{
		m_hitFlag = _hitFlag;
	}

	// アクティブフラグの取得
	bool GetActiveFlag() const
	{
		return m_activeFlag;
	}

	// アクティブフラグの設定
	void SetActiveFlag(const bool _flag)
	{
		m_activeFlag = _flag;
	}

	// 体力の取得
	int GetLife() const
	{
		return m_life;
	}

	// 弾のヒットフラグ設定
	void SetBulletHitFlag(const bool& _isHitFlag)
	{
		m_pWeapon->SetBulletHitFlag(_isHitFlag);
	}
	// 弾の番号取得
	void SetBulletNumber(const int& _bulletNumber)
	{
		m_pWeapon->SetBulletNumber(_bulletNumber);
	}

	// 当たり判定の取得
	Collision::Sphere GetCollider() const
	{
		return m_collider;
	}

public: // 関数

	// 初期化
	void Initialize();
	// 更新
	void Update() override;
	// 描画
	void Render(const DirectX::SimpleMath::Matrix& _view) override;
	// 後始末
	void Finalize();

	// 衝突
	void OnCollision();

private: // サブ関数

	// 点滅
	void Blink();

	// TODO: タグ判定
	// 衝突
	void OnCollision(GameObject* _object);


private: // 変数

	// キーボード
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboardTracker;

	// マウストラッカー
	DirectX::Mouse::ButtonStateTracker m_mouseTracker;

	ID3D11DeviceContext* m_context;

private:

	// プレイヤー
	std::unique_ptr<DirectX::Model>				 m_pPlayer;
	Collision::Sphere							 m_collider;

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
	// 点滅時間
	int											 m_blinkTime;
	// Shiftボタンフラグ
	bool										 m_isShiftDown;
	// 体力
	int											 m_life;
	// アクティブフラグ
	bool										 m_activeFlag;

	// サウンド
	IDirectSoundBuffer8* m_shotSound;

public:

	// 銃
	std::unique_ptr<Weapon>						 m_pWeapon;

};