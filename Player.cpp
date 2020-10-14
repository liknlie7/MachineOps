#include "pch.h"

#include "Player.h"
#include "Bullet.h"

const DirectX::SimpleMath::Vector3 Player::RANGE_MIN = DirectX::SimpleMath::Vector3(-18.5f, 0.0f, -19.0f);
const DirectX::SimpleMath::Vector3 Player::RANGE_MAX = DirectX::SimpleMath::Vector3(18.0f, 0.0f, 19.8f);


// TODO:ステート管理にする
// TODO: タグ判定

// コンストラクタ
Player::Player()
	: m_state(STATE_NORMAL)
	, m_mousePos(0.0f, 0.0f, 0.0f)
	, m_shotInterval(15.0f)
	, m_hitFlag(false)
	, m_blinkTime(30)
	, m_angle(0.0f)
	, m_isShiftDown(false)
	, m_life(1)
	, m_activeFlag(true)
	, m_accel(0.0f, 0.0f, 0.0f)
{
	// 武器の作成
	//m_pWeapon = std::make_unique<Weapon>();

	// プレイヤーモデルのshared_ptrを受け取る
	m_pPlayer = std::weak_ptr<DirectX::Model>(ResourceManager::GetInstance()->GetModel(L"Resources/Models/tank.cmo"));

	// サウンドのshared_ptrを受け取る
	//m_pSound = std::weak_ptr<Adx2Le>(ResourceManager::GetInstance()->GetSound(L"Resources\\Sounds\\PlayScene"));
}


// デストラクタ
Player::~Player()
{
	//m_pSound.reset();
}

// 初期化
void Player::Initialize()
{
	// KeyboardStateTrackerオブジェクトを生成する 
	m_keyboardTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();

	// コライダー
	m_collider.radius = 1.0f;
	m_collider.center = m_position;

	// 銃の作成
	//m_pWeapon->Initialize();

	// 弾の配列を確保する
	//m_pBullets.resize(BulletManager::NUM_BULLET);
	

}

// 更新
void Player::Update()
{
	// キーボードの状態を取得する
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	// キーボードトラッカーを更新する
	m_keyboardTracker->Update(keyState);

	// マウスの状態を取得する
	DirectX::Mouse::State mouseState = DirectX::Mouse::Get().GetState();
	// マウストラッカーを更新する
	m_mouseTracker.Update(mouseState);

	// 速度初期化
	m_velocity = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

	if (keyState.IsKeyUp(DirectX::Keyboard::Keys::LeftShift)) m_isShiftDown = false;
	if (keyState.IsKeyDown(DirectX::Keyboard::Keys::LeftShift)) m_isShiftDown = true;

	if (!m_isShiftDown)
	{
		// Wを押下
		if (keyState.W) m_velocity.z = -0.2f;
		// Aを押下
		if (keyState.A) m_velocity.x = -0.2f;
		// Sを押下
		if (keyState.S) m_velocity.z = +0.2f;
		// Dを押下
		if (keyState.D) m_velocity.x = +0.2f;
	}
	else
	{
		// Wを押下
		if (keyState.W) m_velocity.z = -0.1f;
		// Aを押下
		if (keyState.A) m_velocity.x = -0.1f;
		// Sを押下
		if (keyState.S) m_velocity.z = +0.1f;
		// Dを押下
		if (keyState.D) m_velocity.x = +0.1f;

	}

	if (m_hitFlag)
		Blink();

	if (m_enemyHitFlag) {
		m_velocity = DirectX::SimpleMath::Vector3::Zero;
		m_enemyHitFlag = false;
	}

	// 速度代入
	m_position += m_velocity;

	// 範囲外から出ないようにする
	m_position.x = Clamp(m_position.x, RANGE_MIN.x, RANGE_MAX.x);
	m_position.z = Clamp(m_position.z, RANGE_MIN.z, RANGE_MAX.z);


	m_dir = m_mousePos - m_position;
	m_dir.Normalize();

	m_angle = atan2(m_dir.x, m_dir.z);
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(m_position));
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateRotationY(m_angle);

	m_matrix = rotate * trans;

	// 弾を発射する
	m_shotInterval++;

	if (m_shotInterval > 7.0f)
	{
		// 左クリック
		if (mouseState.leftButton)
		{
			// 弾の生成
			//m_pWeapon->CreateBullet();

			// 射撃音の再生
			//if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
			//	sptr->Play(CRI_PLAYER_SHOT);
			
			//for (int i = 0; m_pBullets.size(); i++)
			//{
			//	// 弾が使用中でないとき
			//	if (m_pBullets[i] == nullptr)
			//	{
			//		// 弾を発射する
			//		m_pBullets[i] = m_pBulletManager->Create(m_position, DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.8f), m_angle);
			//	}
			//}

			m_shotInterval = 0;
		}
	}

	// 武器の更新
	//m_pWeapon->SetAngle(m_angle);
	//m_pWeapon->SetPlayerPos(m_position);
	//m_pWeapon->Update();

	m_collider.center = m_position;

}

// 描画
void Player::Render(const DirectX::SimpleMath::Matrix& _view)
{
	ID3D11DeviceContext1* context = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	DirectX::CommonStates* state = GameContext::Get<DirectX::CommonStates>();
	DirectX::SimpleMath::Matrix proj = GameContext::Get<Projection>()->GetMatrix();

	// プレイヤー描画
	if (m_blinkTime % 5 == 0)
		if (std::shared_ptr<DirectX::Model> sptr = m_pPlayer.lock())
		{
			sptr->Draw(context, *state, m_matrix, _view, proj);
		}

	// 武器の描画
	//m_pWeapon->Render(_view);
}

// 後始末
void Player::Finalize()
{

}

// 衝突
void Player::OnCollision(GameObject* _object)
{
	_object;
}

// 衝突
void Player::OnCollision()
{
	m_hitFlag = true;

	//m_life--;
}

// エネミーとの衝突
void Player::OnCollisionEnemy(DirectX::SimpleMath::Vector3 _enemyPos)
{
	DirectX::SimpleMath::Vector3 v = m_position - _enemyPos;
	v.Length();

}

// 点滅
void Player::Blink()
{
	m_blinkTime--;

	if (m_blinkTime < 0)
	{
		m_hitFlag = false;
		m_blinkTime = 30;
	}
}

void Player::AddForce(float angle, float force)
{
	// 進行方向ベクトル
	DirectX::SimpleMath::Vector3 dir(0.0f, 0.0f, -1.0f);

	// 自機の向きベクトルを求める
	DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::CreateRotationY(angle);
	dir = DirectX::SimpleMath::Vector3::Transform(dir, rotY);

	// 加速度
	m_accel = dir * force;

	// 速度に加速度を足す
	m_velocity += m_accel;
}
