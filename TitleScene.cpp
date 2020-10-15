#include "pch.h"

#include "TitleScene.h"
#include "GameContext.h"
#include "ResourceManager.h"
#include "TitleSoundSeet.h"
#include "EffectMask.h"

// タイトル位置
const DirectX::SimpleMath::Vector2 TitleScene::TITLE_POSITION = DirectX::SimpleMath::Vector2(190.0f, 220.0f);

// タイトル拡大率
const DirectX::SimpleMath::Vector2 TitleScene::TITLE_SCALE = DirectX::SimpleMath::Vector2(0.8f, 0.8f);

// テキスト位置
const DirectX::SimpleMath::Vector2 TitleScene::TEXT_POSITION = DirectX::SimpleMath::Vector2(380.0f, 450.0f);

// テキスト拡大率
const DirectX::SimpleMath::Vector2 TitleScene::TEXT_SCALE = DirectX::SimpleMath::Vector2(0.3f, 0.3f);

// コンストラクタ
TitleScene::TitleScene()
	: m_time(0)
{
	// トラッカーの設定
	m_pKeyboardTracker = GameContext::Get<DirectX::Keyboard::KeyboardStateTracker>();

	// サウンドのshared_ptrを受け取る
	m_pSound = std::weak_ptr<Adx2Le>(ResourceManager::GetInstance()->GetSound(L"Resources\\Sounds\\TitleSounds"));
}

// デストラクタ
TitleScene::~TitleScene()
{
	// サウンドのリンクをクリア
	m_pSound.reset();
}

// 初期化
void TitleScene::Initialize()
{
	// テクスチャデータを受け取る
	m_pTextures[TITLE] = ResourceManager::GetInstance()->GetTexture(L"Resources\\Textures\\Title.png");
	m_pTextures[BACK_GROUND] = ResourceManager::GetInstance()->GetTexture(L"Resources\\Textures\\BackGround.png");
	m_pTextures[TEXT] = ResourceManager::GetInstance()->GetTexture(L"Resources\\Textures\\Massage.png");

	// BGMの再生
	if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
		sptr->Play(CRI_TITLE_TITLEBGM);
}

// 更新
void TitleScene::Update(DX::StepTimer const& _timer)
{
	// フェードエフェクトの取得
	auto effectMask = GameContext::Get<EffectMask>();

	// 経過時間の更新
	float elapsedTime = float(_timer.GetElapsedSeconds());
	m_time += elapsedTime;

	// キーボードの取得
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	// キーボードトラッカー更新
	m_pKeyboardTracker->Update(keyState);

	// スペースキーを押したら
	if (m_pKeyboardTracker->pressed.Space)
	{
		// スタート音の再生
		if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
			sptr->Play(CRI_TITLE_STARTSE);

		// フェードアウト
		effectMask->Close();
	}

	// 画面が閉じるまでまつ
	if (effectMask->IsClose())
	{
		// サウンドを停止させる
		if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
			sptr->Stop();

		// プレイシーンへ遷移
		SceneManager::GetInstance()->RequestScene(eScene::PLAY);
	}
}

// 描画
void TitleScene::Render()
{
	// スプライトバッチの取得
	DirectX::SpriteBatch* spriteBatch = GameContext::Get<DirectX::SpriteBatch>();

	spriteBatch->Begin();

	// 背景描画
	spriteBatch->Draw(m_pTextures[BACK_GROUND].Get(), DirectX::SimpleMath::Vector2::Zero);

	// タイトル描画
	spriteBatch->Draw(m_pTextures[TITLE].Get(), TITLE_POSITION, nullptr,
		DirectX::Colors::White, 0.0f, DirectX::SimpleMath::Vector2::Zero,
		TITLE_SCALE);

	// テキスト描画
	// 点滅させる
	if (sin(m_time * 4) > 0) {
		spriteBatch->Draw(m_pTextures[TEXT].Get(), TEXT_POSITION, nullptr,
			DirectX::Colors::White, 0.0f, DirectX::SimpleMath::Vector2::Zero,
			TEXT_SCALE);
	}

	spriteBatch->End();
}