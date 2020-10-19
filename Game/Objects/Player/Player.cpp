#include "../../pch.h"

#include <CommonStates.h>

#include "../../Manager/ResourceManager.h"
#include "../../Common/DeviceResources.h"
#include "../../Common/Utilities.h"
#include "../../Common/Projection.h"
#include "../../Common/GameContext.h"
#include "../../Sound/PlayerSound.h"
#include "../Bullet.h"
#include "Player.h"

// 移動制限範囲
const DirectX::SimpleMath::Vector3 Player::RANGE_MIN = DirectX::SimpleMath::Vector3(-18.5f, 0.0f, -19.0f);
const DirectX::SimpleMath::Vector3 Player::RANGE_MAX = DirectX::SimpleMath::Vector3(18.0f, 0.0f, 19.8f);

// 弾の速度
const float Player::BULLET_SPEED = 0.8f;

// 弾を撃つ間隔
const float Player::SHOT_INTERVAL = 7.0f;

// プレイヤー移動速度
const float Player::MOVE_SPEED = 0.2f;

// プレイヤー移動速度(シフト押し)
const float Player::MOVE_SLOW_SPEED = 0.1f;

// コンストラクタ
Player::Player()
	: m_mousePos(DirectX::SimpleMath::Vector3::Zero)
	, m_shotInterval(SHOT_INTERVAL)
	, m_hitFlag(false)
	, m_angle(0.0f)
	, m_isShiftDown(false)
{
	// プレイヤーモデルのshared_ptrを受け取る
	m_pPlayer = std::weak_ptr<DirectX::Model>(ResourceManager::GetInstance()->GetModel(L"Resources/Models/tank.cmo"));

	// サウンドのshared_ptrを受け取る
	m_pSound = std::weak_ptr<Adx2Le>(ResourceManager::GetInstance()->GetSound(L"Resources\\Sounds\\PlayScene"));
}

// デストラクタ
Player::~Player()
{
	m_pSound.reset();
}

// 初期化
void Player::Initialize()
{
	// KeyboardStateTrackerオブジェクトを生成する 
	m_keyboardTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();

	// コライダー設定
	m_collider.radius = 1.0f;
	m_collider.center = m_position;
}

// 更新
void Player::Update()
{
	// 移動
	Move();

	// 弾を撃つ
	Shot();

	// コライダーの中心を設定
	m_collider.center = m_position;
}

// 描画
void Player::Render(const DirectX::SimpleMath::Matrix& _view)
{
	ID3D11DeviceContext1* context = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	DirectX::CommonStates* state = GameContext::Get<DirectX::CommonStates>();
	DirectX::SimpleMath::Matrix proj = GameContext::Get<Projection>()->GetMatrix();

	// プレイヤー描画
	if (std::shared_ptr<DirectX::Model> sptr = m_pPlayer.lock())
	{
		sptr->Draw(context, *state, m_matrix, _view, proj);
	}
}

// 衝突
void Player::OnCollision()
{
	m_hitFlag = true;
}

// 移動
void Player::Move()
{
	// キーボードの状態を取得する
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	// キーボードトラッカーを更新する
	m_keyboardTracker->Update(keyState);

	// 速度初期化
	m_velocity = DirectX::SimpleMath::Vector3::Zero;

	if (keyState.IsKeyUp(DirectX::Keyboard::Keys::LeftShift)) m_isShiftDown = false;
	if (keyState.IsKeyDown(DirectX::Keyboard::Keys::LeftShift)) m_isShiftDown = true;

	if (!m_isShiftDown)
	{
		// Wを押下
		if (keyState.W) m_velocity.z = -MOVE_SPEED;
		// Aを押下
		if (keyState.A) m_velocity.x = -MOVE_SPEED;
		// Sを押下
		if (keyState.S) m_velocity.z = +MOVE_SPEED;
		// Dを押下
		if (keyState.D) m_velocity.x = +MOVE_SPEED;
	}
	else
	{
		// Wを押下
		if (keyState.W) m_velocity.z = -MOVE_SLOW_SPEED;
		// Aを押下
		if (keyState.A) m_velocity.x = -MOVE_SLOW_SPEED;
		// Sを押下
		if (keyState.S) m_velocity.z = +MOVE_SLOW_SPEED;
		// Dを押下
		if (keyState.D) m_velocity.x = +MOVE_SLOW_SPEED;
	}

	// 速度代入
	m_position += m_velocity;

	// 範囲外から出ないようにする
	m_position.x = Clamp(m_position.x, RANGE_MIN.x, RANGE_MAX.x);
	m_position.z = Clamp(m_position.z, RANGE_MIN.z, RANGE_MAX.z);

	// 向きを計算
	m_dir = m_mousePos - m_position;
	m_dir.Normalize();

	// マウスの方へ向ける
	m_angle = atan2(m_dir.x, m_dir.z);
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(m_position));
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateRotationY(m_angle);

	m_matrix = rotate * trans;
}

// 弾を撃つ
void Player::Shot()
{
	// マウスの状態を取得する
	DirectX::Mouse::State mouseState = DirectX::Mouse::Get().GetState();

	// マウストラッカーを更新する
	m_mouseTracker.Update(mouseState);

	// 弾を発射する
	m_shotInterval++;

	if (m_shotInterval > SHOT_INTERVAL)
	{
		// 左クリック
		if (mouseState.leftButton)
		{
			// 弾の生成
			m_pBulletManager->CreateBullet(m_position, BULLET_SPEED, m_angle, m_pBulletManager->GetBulletGeometry(BulletManager::BOX), "BOX");

			// 射撃音の再生
			if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
			{
				sptr->Play(CRI_PLAYER_SHOT);
			}

			m_shotInterval = 0;
		}
	}
}