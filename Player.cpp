#include "pch.h"

#include "Player.h"
#include "Bullet.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using namespace std;

// TODO:ステート管理にする

// コンストラクタ
Player::Player(const std::string& _tag)
	: GameObject(_tag)
	, m_mousePos(0.0f, 0.0f, 0.0f)
	, m_shotInterval(15.0f)
	, m_hitFlag(false)
	, m_blinkTime(30)
	, m_angle(0.0f)
	, m_isShiftDown(false)
	, m_life(1)
	, m_activeFlag(true)
{
	m_pWeapon = make_unique<Weapon>();
	//m_shotSound = GameContext::Get<Sound>()->GetSound(0);
}


// デストラクタ
Player::~Player()
{
}

// 初期化
void Player::Initialize()
{
	// KeyboardStateTrackerオブジェクトを生成する 
	m_keyboardTracker = std::make_unique<Keyboard::KeyboardStateTracker>();

	// モデル作成 
	EffectFactory* factory = new EffectFactory(GameContext::Get<DX::DeviceResources>()->GetD3DDevice());
	factory->SetDirectory(L"Resources/Models");
	m_pPlayer = Model::CreateFromCMO(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources/Models/tank.cmo", *factory);
	delete factory;

	m_activeFlag = true;

	m_life = 1;

	// コライダー
	m_collider.radius = 1.0f;
	m_collider.center = m_position;

	// 銃の作成
	m_pWeapon->Initialize();

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
	m_velocity = Vector3(0.0f, 0.0f, 0.0f);

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
		if (keyState.W)
		{
			m_velocity.z = -0.1f;
			//m_shotSound->Play(0,0,0);
		}
		// Aを押下
		if (keyState.A) m_velocity.x = -0.1f;
		// Sを押下
		if (keyState.S) m_velocity.z = +0.1f;
		// Dを押下
		if (keyState.D) m_velocity.x = +0.1f;

	}

	if (m_hitFlag)  
		Blink();


	// 速度代入
	m_position += m_velocity;

	m_dir = m_mousePos - m_position;
	m_dir.Normalize();

	m_angle = atan2(m_dir.x, m_dir.z);
	Matrix trans = Matrix::CreateTranslation(Vector3(m_position));
	Matrix rotate = Matrix::CreateRotationY(m_angle);

	m_matrix = rotate * trans;

	// 弾を発射する
	m_shotInterval++;
	
	if (m_shotInterval > 7.0f)
	{
		// 左クリック
		if (mouseState.leftButton)
		{
			// 弾の生成
			m_pWeapon->CreateBullet();
			m_shotInterval = 0;
		}
	}

	// 武器の更新
	m_pWeapon->SetAngle(m_angle);
	m_pWeapon->SetPlayerPos(m_position);
	m_pWeapon->Update();

	m_collider.center = m_position;

}

// 描画
void Player::Render(const Matrix& _view)
{
	// プレイヤー描画
	if (m_blinkTime % 5 == 0)
		m_pPlayer->Draw(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(),
			*GameContext::Get<CommonStates>(), m_matrix, _view, GameContext::Get<Projection>()->GetMatrix());

	// 武器の描画
	m_pWeapon->Render(_view);
}

// 後始末
void Player::Finalize()
{

}

// 衝突
void Player::OnCollision(GameObject* _object)
{

}

// 衝突
void Player::OnCollision()
{
	m_hitFlag = true;

	//m_life--;
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