#pragma once

#include <SimpleMath.h>
#include <GeometricPrimitive.h>
#include <Model.h>
#include <Effects.h>
#include <CommonStates.h>

#include "DeviceResources.h"
#include "Projection.h"
#include "GameObject.h"
#include "GameContext.h"

// 敵
class Enemy : public GameObject
{
public: // 基本

	// コンストラクタ
	Enemy();
	// デストラクタ
	~Enemy();

public: // アクセサ

	DirectX::SimpleMath::Vector3 Enemy::GetPos()
	{
		return m_pos;
	}

	DirectX::SimpleMath::Matrix Enemy::GetMat()
	{
		return m_mat;
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
	void DownLife(int _damege)
	{
		m_life -= _damege;
	}


public: // 関数

	// 初期化
	void InitializeNormal(DirectX::SimpleMath::Vector3 _pos = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
	void InitializeShield(DirectX::SimpleMath::Vector3 _pos = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
	// 更新
	void Update() override;
	void UpdateNormal(DirectX::SimpleMath::Vector3 _playerPos);
	void UpdateShield(DirectX::SimpleMath::Vector3 _playerPos);
	// 描画
	void Render(const DirectX::SimpleMath::Matrix& _view) override;
	// 後始末
	void Finalize();

	// プレイヤーを追いかける
	void ChasePlayer(DirectX::SimpleMath::Vector3 _playerPos);
	// 点滅
	void Blink();

private: // 変数

	// 敵
	std::unique_ptr<DirectX::Model>	m_pEnemy;

	//当たり判定用
	std::unique_ptr<DirectX::GeometricPrimitive> m_pDecisionArea;
	DirectX::SimpleMath::Vector3				 m_decisionAreaPos;
	DirectX::SimpleMath::Matrix					 m_decisionAreaMat;

	// 速さ
	float											m_speed;
	// 体力
	int												m_life;
	// ヒットフラグ
	bool											m_hitFlag;
	// 点滅時間
	int												m_blinkTime;
};