#include "pch.h"

#include "PlayState.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using namespace std;

PlayState::PlayState()
	: GameState()
	, m_pDebugCamera()
	, m_pGridFloor()
{

}


PlayState::~PlayState()
{
}


void PlayState::Initialize()
{

	m_pDeviceResources = GameContext::Get<DX::DeviceResources>();
	m_pDevice = m_pDeviceResources->GetD3DDevice();
	m_pDeviceContext = m_pDeviceResources->GetD3DDeviceContext();
	m_pProjection = GameContext::Get<Projection>();
	RECT size = m_pDeviceResources->GetOutputSize();

	// デバッグカメラの作成
	m_pDebugCamera = make_unique<DebugCamera>();

	// デバッグフロアの作成
	m_pGridFloor = make_unique<GridFloor>(10.0f, 10);

	// コモンステートの作成
	m_pState = GameContext::Get<CommonStates>();

	// 追尾カメラの作成
	m_pFollowCamera = make_unique<FollowCamera>();
	m_pFollowCamera->Initialize();

	// フロア作成
	m_pFloor = make_unique<Floor>();
	m_pFloor->Initialize();

	// プレイヤー作成
	m_pPlayer = make_unique<Player>();
	m_pPlayer->Initialize();

	// 敵作成
	m_pEnemy = make_unique<Enemy>(m_pEnemy->BOSS_TYPE);
	m_pEnemy->Initialize(Vector3(0.0f, 1.0f, -15.0f));

	m_color = Colors::Red;

	m_viewPort =
		Matrix::CreateScale(Vector3(.5f, -.5f, 1.f)) *
		Matrix::CreateTranslation(Vector3(.5f, .5f, 0.f)) *
		Matrix::CreateScale(Vector3(float(size.right), float(size.bottom), 1.f));

	//デバッグ用
	geo = GeometricPrimitive::CreateSphere(m_pDeviceResources->GetD3DDeviceContext(), 1.0f);

}

void PlayState::Update()
{
	Mouse::State mouseState = Mouse::Get().GetState();
	Keyboard::State keyState = Keyboard::Get().GetState();

	if (keyState.IsKeyDown(Keyboard::Space))
	{
		GameStateManager* gameStateManager = GameContext::Get<GameStateManager>();
		gameStateManager->RequestState("Title");
	}

	// プレイヤー更新
	m_pPlayer->Update();

	// 敵更新
	m_pEnemy->SetPlayerPos(m_pPlayer->GetPos());
	m_pEnemy->Update();

	// デバッグカメラ更新
	m_pDebugCamera->update();

	// 追尾カメラ更新
	m_pFollowCamera->Update(m_pPlayer->GetPos() + FollowCamera::EYE_VEC, m_pPlayer->GetPos());

	m_color = Colors::Red;

	// マウス座標をワールド座標へ変換
	// マウスRayの作成
	Vector3 mousePos = Vector3::Transform(Vector3((float)mouseState.x, (float)mouseState.y, 0), m_viewPort.Invert());
	Vector3 pointNear = Vector3(mousePos.x, mousePos.y, 0.0f);
	Vector3 pointFar = Vector3(mousePos.x, mousePos.y, 1.0f);
	Matrix inverseviewproj = (m_pFollowCamera->getViewMatrix() *  m_pProjection->GetMatrix()).Invert();
	Vector3 rayNear = Vector3::Transform(pointNear, inverseviewproj);
	Vector3 rayFar = Vector3::Transform(pointFar, inverseviewproj);
	Vector3 raySubtraction = rayFar - rayNear;
	Vector3 rayDirection = raySubtraction;
	// 正規化
	rayDirection.Normalize();

	// 頂点ベクトル
	Vector3 v0 = Vector3(-50.0f, 0.0f, -50.0f);  // 左上
	Vector3 v1 = Vector3(-50.0f, 0.0f, 50.0f);   // 左下
	Vector3 v2 = Vector3(50.0f, 0.0f, 50.0f);    // 右下
	Vector3 v3 = Vector3(50.0f, 0.0f, -50.0f);   // 右上

	// 交差点
	Vector3 hitPos;

	// 三角形を作成
	Collision::Triangle tri1(v0, v2, v1);
	Collision::Triangle tri2(v0, v3, v2);

	// マウスRayと三角形の当たり判定(交差点検出)
	if (Collision::IntersectSegmentTriangle(rayNear, rayFar, tri1, &hitPos) ||
		Collision::IntersectSegmentTriangle(rayNear, rayFar, tri2, &hitPos))
	{
		m_pPlayer->SetMousePos(hitPos);
		geoVec = hitPos;
	}

	// 交差地点デバッグ
	geoMat = Matrix::CreateTranslation(geoVec);

	// 弾の中心と半径を設定
	vector<Vector3> playerBullets = m_pPlayer->GetBulletPos();
	vector<Vector3> enemyBullets = m_pEnemy->GetBulletPos();

	vector<Collision::Sphere> playerBullet;
	vector<Collision::Sphere> enemyBullet;

	playerBullet.resize(playerBullets.size());
	enemyBullet.resize(enemyBullets.size());

	for (unsigned int i = 0; i < playerBullets.size(); i++)
	{
		playerBullet[i].center = playerBullets[i];
		playerBullet[i].radius = 0.15f;
	}
	for (unsigned int i = 0; i < enemyBullets.size(); i++)
	{
		enemyBullet[i].center = enemyBullets[i];
		enemyBullet[i].radius = 0.15f;
	}

	for (unsigned int i = 0; i < playerBullet.size(); i++)
	{
		if (Collision::HitCheckSphereToSphere(m_pEnemy->GetCollider(), playerBullet[i]))
		{
			m_pEnemy->OnCollision();
			m_pPlayer->m_pWeapon->BulletOnCollision(i);
		}
	}
	for (unsigned int i = 0; i < enemyBullet.size(); i++)
	{
		if (Collision::HitCheckSphereToSphere(m_pPlayer->GetCollider(), enemyBullet[i]))
		{
			//m_pPlayer->OnCollision();
			m_pEnemy->BulletOnCollision(i);
		}
	}

	// プレイヤーと敵との接触判定
	if (!m_pPlayer->GetHitFlag())
		if (Collision::HitCheckSphereToSphere(m_pPlayer->GetCollider(), m_pEnemy->GetCollider()))
			m_pPlayer->SetHitFlag(true);

	// リザルトシーンへ遷移
	if (m_pEnemy->GetModel() == nullptr)
	{
		GameStateManager* gameStateManager = GameContext::Get<GameStateManager>();
		gameStateManager->RequestState("Result");
	}
}


void PlayState::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 10, L"PlayState");
	debugFont->draw();
	debugFont->print(10, 40, L"[Space] Title");
	debugFont->draw();

	// プレイヤー表示
	m_pPlayer->Render(m_pFollowCamera->getViewMatrix());

	// 敵表示
	m_pEnemy->Render(m_pFollowCamera->getViewMatrix());

	// 床の表示
	m_pFloor->Render(m_pFollowCamera->getViewMatrix());

	//-----デバッグ用(これ以外すべて消す----------------------------------
	Projection* proj = GameContext::Get<Projection>();

	geo->Draw(geoMat, m_pFollowCamera->getViewMatrix(), proj->GetMatrix(), Colors::Red);

	// デバッグ用床の表示
	//m_pDebugFloor->Draw(context, debugCamera->getViewMatrix(), m_projection);

	//// プレイヤー表示
	////m_pPlayer->Render(*m_pState.get(), debugCamera->getViewMatrix(), m_projection, m_color);

	//// 敵表示
	////m_pEnemy->Render(deviceResources->GetD3DDeviceContext(), *m_pState.get(), m_pFollowCamera->getViewMatrix(), m_projection, static_cast<Vector4>(Colors::Blue));

	//// 床の表示
	////m_pFloor->Render(deviceResources->GetD3DDeviceContext(), *m_pState.get(), m_pDebugCamera->getViewMatrix(), m_projection);

	//----------------------------------------------------------------

}


void PlayState::Finalize()
{
	m_pDebugCamera.reset();
	m_pGridFloor.reset();
}