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

	m_pDeviceResources = GameContext<DX::DeviceResources>::Get();
	m_pDevice = m_pDeviceResources->GetD3DDevice();
	m_pDeviceContext = m_pDeviceResources->GetD3DDeviceContext();
	m_pProjection = GameContext<Projection>().Get();
	RECT size = m_pDeviceResources->GetOutputSize();

	//float aspectRatio = float(size.right) / float(size.bottom);

	// 画角を設定
	//float fovAngleY = XMConvertToRadians(45.0f);

	//// 射影行列を作成する
	//m_pProjection->SetPerspectiveFieldOfView(fovAngleY, aspectRatio, 0.01f, 1000.f);

	// デバッグカメラの作成
	m_pDebugCamera = make_unique<DebugCamera>();

	// デバッグフロアの作成
	m_pGridFloor = make_unique<GridFloor>(10.0f, 10);

	// コモンステートの作成
	m_pState = GameContext<CommonStates>().Get();

	// 追尾カメラの作成
	m_pFollowCamera = make_unique<FollowCamera>();
	m_pFollowCamera->Initialize();

	// フロア初期化
	m_pFloor = make_unique<Floor>();
	m_pFloor->Initialize();

	// プレイヤー初期化
	m_pPlayer = make_unique<Player>();
	m_pPlayer->Initialize();

	// 敵初期化
	for (int i = 0; i < 2; i++)
		m_pEnemy1[i] = make_unique<Enemy>();
	m_pEnemy1[0]->InitializeNormal(Vector3(+5.0f, 1.0f, 0.0f));
	m_pEnemy1[1]->InitializeNormal(Vector3(-5.0f, 1.0f, 0.0f));

	for (int i = 0; i < 2; i++)
		m_pEnemy2[i] = make_unique<Enemy>();
	m_pEnemy2[0]->InitializeShield(Vector3(+5.0f, 1.0f, -5.0f));
	m_pEnemy2[1]->InitializeShield(Vector3(-5.0f, 1.0f, -5.0f));

	m_color = Colors::Red;


	m_viewPort =
		Matrix::CreateScale(Vector3(.5f, -.5f, 1.f)) *
		Matrix::CreateTranslation(Vector3(.5f, .5f, 0.f)) *
		Matrix::CreateScale(Vector3(float(size.right), float(size.bottom), 1.f));
}


void PlayState::Update()
{
	Mouse::State mouseState = Mouse::Get().GetState();
	Keyboard::State keyState = Keyboard::Get().GetState();

	if (keyState.IsKeyDown(Keyboard::Space))
	{
		GameStateManager* gameStateManager = GameContext<GameStateManager>().Get();
		gameStateManager->RequestState("Title");
	}

	// プレイヤー更新
	m_pPlayer->Update();

	// 敵更新
	for (int i = 0; i < 2; i++)
	{
		m_pEnemy1[i]->UpdateNormal(m_pPlayer->GetPos());
		m_pEnemy2[i]->UpdateShield(m_pPlayer->GetPos());
	}

	// デバッグカメラ更新
	m_pDebugCamera->update();

	// 追尾カメラ更新
	m_pFollowCamera->Update(m_pPlayer->GetPos() + FollowCamera::EYE_VEC, m_pPlayer->GetPos());

	m_color = Colors::Red;

	// マウス座標をワールド座標へ変換
	// マウスRayの作成
	Vector3 mousePos = Vector3::Transform(Vector3(mouseState.x, mouseState.y, 0), m_viewPort.Invert());
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
	if (Collision::IntersectSegmentTriangle(rayNear, raySubtraction, tri1, &hitPos) ||
		Collision::IntersectSegmentTriangle(rayNear, raySubtraction, tri2, &hitPos))
	{
		m_pPlayer->SetMousePos(hitPos);
	}

	// 敵、弾の中心と半径を設定
	Collision::Sphere enemy1[2], enemy2[2];

	for (int i = 0; i < 2; i++)
	{
		enemy1[i].center = m_pEnemy1[i]->GetPos();					enemy1[i].radius = 1.0f;
		enemy2[i].center = m_pEnemy2[i]->GetPos();					enemy2[i].radius = 1.0f;
	}
	vector<Vector3> bullets = m_pPlayer->GetBulletPos();

	vector<Collision::Sphere> colBullet;
	colBullet.resize(bullets.size());

	for (int i = 0; i < bullets.size(); i++)
	{
		colBullet[i].center = bullets[i];
		colBullet[i].radius = 0.15f;
	}
	for (int i = 0; i < colBullet.size(); i++)
	{
		if (Collision::HitCheckSphereToSphere(enemy1[0], colBullet[i]))
		{
			m_pEnemy1[0]->SetHitFlag(true);
			m_pEnemy1[0]->DownLife(-1);
		}
		if (Collision::HitCheckSphereToSphere(enemy1[1], colBullet[i]))
		{
			m_pEnemy1[1]->SetHitFlag(true);
			m_pEnemy1[1]->DownLife(-1);
		}
		if (Collision::HitCheckSphereToSphere(enemy2[0], colBullet[i]))
		{
			m_pEnemy2[0]->SetHitFlag(true);
			m_pEnemy2[0]->DownLife(-1);
		}
		if (Collision::HitCheckSphereToSphere(enemy2[1], colBullet[i]))
		{
			m_pEnemy2[1]->SetHitFlag(true);
			m_pEnemy2[1]->DownLife(-1);
		}

	}

	// プレイヤーと敵との接触判定
	for (int i = 0; i < 2; i++)
	{
		if (!m_pPlayer->GetHitFlag())
			if (Collision::HitCheckSphereToSphere(m_pPlayer->GetCollider(), enemy1[i]))
				m_pPlayer->SetHitFlag(true);

		if (!m_pPlayer->GetHitFlag())
			if (Collision::HitCheckSphereToSphere(m_pPlayer->GetCollider(), enemy2[i]))
				m_pPlayer->SetHitFlag(true);
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
	for (int i = 0; i < 2; i++)
	{
		m_pEnemy1[i]->Render(m_pFollowCamera->getViewMatrix());
		m_pEnemy2[i]->Render(m_pFollowCamera->getViewMatrix());
	}

	// 床の表示
	m_pFloor->Render(m_pFollowCamera->getViewMatrix());

	//-----デバッグ用(これ以外すべて消す----------------------------------
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