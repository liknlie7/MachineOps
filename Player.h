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


class Bullet;
class Weapon;

class Player : public GameObject
{
public: // 基本

	// コンストラクタ
	Player();
	// デストラクタ
	~Player();

public: // アクセサ

	// 座標の取得
	DirectX::SimpleMath::Vector3 Player::GetPos() const
	{
		return m_pos;
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
	bool Player::GetHitFlag() const
	{
		return m_hitFlag;
	}
	// 接触判定フラグの設定
	void Player::SetHitFlag(const bool& _hitFlag)
	{
		m_hitFlag = _hitFlag;
	}

	void Player::SetBulletHitFlag(const bool& _isHitFlag)
	{
		m_pWeapon->SetBulletHitFlag(_isHitFlag);
	}
	void Player::SetBulletNumber(const int& _bulletNumber)
	{
		m_pWeapon->SetBulletNumber(_bulletNumber);
	}

	Collision::Sphere Player::GetCollider() const
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

	// 点滅
	void Blink();

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

public:

	// 銃
	std::unique_ptr<Weapon>						 m_pWeapon;

};