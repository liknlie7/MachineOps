#include "pch.h"

#include "Player.h"
#include "Bullet.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using namespace std;

// コンストラクタ
Player::Player()
	: m_mousePos(0.0f, 0.0f, 0.0f)
	, m_shotInterval(15.0f)
	, m_hitFlag(false)
	, m_blinkTime(50)
	, m_angle(0.0f)
{
	m_pWeapon = make_unique<Weapon>();
}


// デストラクタ
Player::~Player()
{
}

// 初期化
void Player::Initialize()
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	m_context = deviceResources->GetD3DDeviceContext();

	// KeyboardStateTrackerオブジェクトを生成する 
	m_keyboardTracker = std::make_unique<Keyboard::KeyboardStateTracker>();

	// エフェクトファクトリの作成 
	EffectFactory* factory = new EffectFactory(deviceResources->GetD3DDevice());
	// テクスチャの読み込みパス指定 
	factory->SetDirectory(L"Resources/Models");
	// ファイルを指定してモデルデータ読み込み 
	m_pPlayer = Model::CreateFromCMO(
		deviceResources->GetD3DDevice(),
		L"Resources/Models/tank.cmo",
		*factory
	);
	delete factory;

	// 銃の作成
	m_pWeapon->Initialize();

	m_collider.radius = 1.0f;
	m_collider.center = m_pos;
	
	// 当たり判定用
	//m_pDecisionArea = GeometricPrimitive::CreateSphere(deviceResources->GetD3DDeviceContext(), 2.0f);

	//m_decisionAreaPos = m_pos;

}

// 更新
void Player::Update(DX::StepTimer const& timer)
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
	m_vel = Vector3(0.0f, 0.0f, 0.0f);

	// Wを押下
	if (keyState.W) m_vel.z = -0.2f;
	// Aを押下
	if (keyState.A) m_vel.x = -0.2f;
	// Sを押下
	if (keyState.S) m_vel.z = +0.2f;
	// Dを押下
	if (keyState.D) m_vel.x = +0.2f;
	// Spaceを押下
	//if (keyState.Space && m_pos.y == 0.5f) { m_vel.y = 0.5f; }

	if (m_hitFlag)  Blink();

	// 速度代入
	m_pos += m_vel;

	m_dir = m_mousePos - m_pos;
	m_dir.Normalize();

	m_angle = atan2(m_dir.x, m_dir.z);
	Matrix trans = Matrix::CreateTranslation(Vector3(m_pos));
	Matrix rotate = Matrix::CreateRotationY(m_angle);

	m_mat = rotate * trans;

	// 弾を発射する
	m_shotInterval++;
	if (m_shotInterval > 15.0f)
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
	m_pWeapon->SetPlayerPos(m_pos);
	m_pWeapon->Update(timer);

	m_collider.center = m_pos;  

}

// 描画
void Player::Render(const Matrix& _view)
{
	Projection* proj = GameContext<Projection>().Get();
	CommonStates* state = GameContext<CommonStates>().Get();

	// プレイヤー描画
	if (m_blinkTime % 5 == 0)
		m_pPlayer->Draw(m_context, *state, m_mat, _view, proj->GetMatrix());

	// 武器の描画
	m_pWeapon->Render(_view);

	// 判定用
	//m_pDecisionArea->Draw(m_mat, _view, proj->GetMatrix(), Colors::Red, nullptr, true);

}

// 後始末
void Player::Finalize()
{

}

// 点滅
void Player::Blink()
{
	m_blinkTime--;

	if (m_blinkTime < 0)
	{
		m_hitFlag = false;
		m_blinkTime = 50;
	}
}