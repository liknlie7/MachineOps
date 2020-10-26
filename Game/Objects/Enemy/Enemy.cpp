#include "../../pch.h"

#include "../../Common/DeviceResources.h"
#include "../../Common/Projection.h"
#include "../../Common/GameContext.h"
#include "../../Manager/ResourceManager.h"
#include "../Player/Player.h"
#include "Enemy.h"

// 通常の大きさ
const float Enemy::SIZE = 1.5f;

// ボスの大きさ
const float Enemy::BOSS_SIZE = 8.0f;

// 弾を撃つ間隔
const float Enemy::NORMAL_SHOT_INTERVEL = 15.0f;
const float Enemy::ALL_DIRECTION_SHOT_INTERVEL = 50.0f;
const float Enemy::WHORL_SHOT_INTERVEL = 10.0f;

// 点滅間隔
const int Enemy::BLINK_TIME = 30;

// 弾の速度
const float Enemy::BULLET_SPEED = 0.15f;

// コンストラクタ
Enemy::Enemy(const EnemyData& _enemyData)
	: m_blinkTime(0)
	, m_hitFlag(false)
	, m_playerPos(DirectX::SimpleMath::Vector3::Zero)
	, m_shotInterval(0.0f)
	, m_shotRotate(0.0f)
{
	// エネミー種類設定
	m_enemyType = _enemyData.enemyType;

	// ライフ設定
	m_maxLife = m_life = (float)_enemyData.life;

	// 移動速度設定
	m_moveSpeed = _enemyData.moveSpeed;

	// 当たり判定半径設定
	m_collider.radius = _enemyData.collider;

	// 射撃種類設定
	m_shotType = _enemyData.shotType;
}

// 初期化
void Enemy::Initialize(const DirectX::SimpleMath::Vector3& _pos)
{
	switch (m_enemyType)
	{
	case NORMAL_ENEMY: // ノーマルタイプ

		// 位置初期化
		m_position = _pos;

		// 当たり判定中心点の設定
		m_collider.center = m_position;

		break;

	case SHIELD_ENEMY: // 盾持ち

		// 位置初期化
		m_position = _pos;

		// 当たり判定中心点の設定
		m_collider.center = m_position;

		break;

	case BOSS_ENEMY: // ボス

		// エネミーモデルのshared_ptrを受け取る
		m_pEnemy = std::weak_ptr<DirectX::Model>(ResourceManager::GetInstance()->GetModel(L"Resources/Models/Enemy1.cmo"));

		// 位置初期化
		m_position = _pos;

		// 当たり判定中心点の設定
		m_collider.center = m_position;

		break;
	}
}

// 更新
void Enemy::Update()
{
	// プレイヤーの方向に向ける
	TurnToDirectionPlayer();

	switch (m_enemyType)
	{
	case NORMAL_ENEMY: // ノーマルタイプ

		// プレイヤーを追いかける
		ChasePlayer(m_playerPos);

		break;

	case SHIELD_ENEMY: // 盾持ち

		break;

	case BOSS_ENEMY: // ボス

		// プレイヤーを追いかける
		ChasePlayer(m_playerPos);

		// 射撃パターンの切り替え
		ChangeShotPattern();

		break;
	}

	// 弾を撃つ
	Shot();

	// 速度代入
	m_position += m_velocity;

	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateRotationY(m_enemyAngle);
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(BOSS_SIZE);
	m_matrix = scale * rotate * DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(m_position.x, 1.0f, m_position.z));

	// 当たり判定の中心を位置で設定
	m_collider.center = m_position;

	// ヒットしていたら
	if (m_hitFlag)
	{
		// 点滅させる
		Blink();
	}
}


// 描画
void Enemy::Render(const DirectX::SimpleMath::Matrix& _view)
{
	ID3D11DeviceContext1* context = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	DirectX::CommonStates* state = GameContext::Get<DirectX::CommonStates>();
	DirectX::SimpleMath::Matrix proj = GameContext::Get<Projection>()->GetMatrix();

	// モデル描画
	if (m_blinkTime % 5 == 0)
	{
		if (m_life != 0)
		{
			if (std::shared_ptr<DirectX::Model> sptr = m_pEnemy.lock())
			{
				sptr->Draw(context, *state, m_matrix, _view, proj);
			}
		}
	}
}

// プレイヤーを追いかける
void Enemy::ChasePlayer(const DirectX::SimpleMath::Vector3& _playerPos)
{
	// プレイヤーへの向きを計算
	DirectX::SimpleMath::Vector3 dir = _playerPos - m_position;
	dir.Normalize();

	// エネミーの移動
	m_position += dir * m_moveSpeed;
}

// 点滅
void Enemy::Blink()
{
	m_blinkTime--;

	if (m_blinkTime < 0)
	{
		m_hitFlag = false;
		m_blinkTime = BLINK_TIME;
	}
}

// 射撃パターンの切り替え
void Enemy::ChangeShotPattern()
{
	// HPの割合でパターンを変える
	if ((m_life / m_maxLife) * 100 <= 70 && (m_life / m_maxLife) * 100 > 40)
	{
		m_shotType = WHORL_SHOT;
	}
	if ((m_life / m_maxLife) * 100 <= 40)
	{
		m_shotType = ALL_DIRECTION_SHOT;
	}
}

// プレイヤーの方向を向く
void Enemy::TurnToDirectionPlayer()
{
	// プレイヤーの方を向く
	DirectX::SimpleMath::Vector3 m_dir;
	m_dir = m_playerPos - m_position;
	m_dir.Normalize();
	m_enemyAngle = atan2(m_dir.x, m_dir.z);
}

// 弾を撃つ
void Enemy::Shot()
{
	m_shotInterval++;
	switch (m_shotType)
	{
	case NORMAL_SHOT: // 通常
	{
		if (m_shotInterval > NORMAL_SHOT_INTERVEL)
		{
			// 弾の生成
			m_pBulletManager->CreateBullet(m_position, BULLET_SPEED, m_enemyAngle, m_pBulletManager->GetBulletGeometry(BulletManager::SPHERE), "SPHERE");

			m_shotInterval = 0;

			break;
		}
	}
	case ALL_DIRECTION_SHOT: // 全方位
	{
		if (m_shotInterval > ALL_DIRECTION_SHOT_INTERVEL)
		{
			for (int rad = 0; rad < 130; rad += 6)
			{
				// 弾の生成
				m_pBulletManager->CreateBullet(m_position, BULLET_SPEED, (float)rad + m_enemyAngle, m_pBulletManager->GetBulletGeometry(BulletManager::SPHERE), "SPHERE");

				m_shotInterval = 0;
			}
		}
		break;
	}
	case WHORL_SHOT:

		if (m_shotInterval > WHORL_SHOT_INTERVEL)
		{
			for (int i = 0; i < 5; i++)
			{
				// 弾の生成
				m_pBulletManager->CreateBullet(m_position, BULLET_SPEED, m_shotRotate, m_pBulletManager->GetBulletGeometry(BulletManager::SPHERE), "SPHERE");

				m_shotRotate += 0.2f;
				m_shotInterval = 0;
				i++;
			}
		}
		break;
	default:
		break;
	}
}

// 衝突した時
void Enemy::OnCollision()
{
	// HPを減らす
	m_life--;

	m_hitFlag = true;
}