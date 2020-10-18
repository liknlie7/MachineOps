#pragma once

#include <SimpleMath.h>
#include <Effects.h>
#include <SpriteBatch.h>

#include "SceneManager.h"
#include "WICTextureLoader.h" 
#include "StepTimer.h"
#include "Adx2Le.h"
#include "FollowCamera.h"
#include "Floor.h"
#include "Wall.h"
#include "Player.h"
#include "Enemy.h"
#include "MouseCursor.h"
#include "WarningEffect.h"
#include "BulletManager.h"

// プレイシーンクラス
class PlayScene : public IScene
{
public:

	// ゲームステート
	enum GAME_STATE
	{
		STATE_START,		// ゲーム開始
		STATE_GAME,			// ゲーム中
	};

	// ウェーブ
	enum WAVE_STATE
	{
		NORMAL_WAVE,		// 通常ウェーブ
		BOSS_WAVE,			// ボスウェーブ
	};

public: // 基本

	// コンストラクタ
	PlayScene();

	// デストラクタ
	virtual ~PlayScene();

public: // 関数

	// 初期化
	void Initialize() override;

	// 更新
	void Update(DX::StepTimer const& _timer) override;
	
	// 描画
	void Render() override;
	
	// 後始末
	void Finalize() override {};

private: // サブ関数

	// 線形補間
	float Lerp(float _start, float _end, float _time);

private: // 定数

	// エネミー(ボス)初期位置
	static const DirectX::SimpleMath::Vector3 ENEMY_BOSS_INIT_POS;

	// ライフゲージ減少にかかる時間
	static const float DAMAGE_TIME;

	// HPゲージスケール値
	static const float HP_SCALE_X;
	static const float HP_SCALE_Y;

	// HPゲージ位置
	static const DirectX::SimpleMath::Vector2 HP_RED_POS;
	static const DirectX::SimpleMath::Vector2 HP_GREEN_POS;

	// 薄いゲージ用
	static const DirectX::SimpleMath::Vector4 HP_GAUGE_COLOR;

	// テクスチャ
	enum Texture
	{
		GREEN_HP,	// 緑HP
		RED_HP,		// 赤HP

		ALL,		// 全てのテクスチャ
	};

private: // 変数

	// サウンド
	std::weak_ptr<Adx2Le>								m_pSound;

	// エフェクト
	std::unique_ptr<DirectX::BasicEffect>				m_batchEffect;

	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_primitiveBatch;

	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			m_inputLayout;
	// ゲームの状態
	GAME_STATE											m_gameState;

	// ウェーブの状態
	WAVE_STATE											m_waveState;

	// エフェクト
	std::unique_ptr<DirectX::BasicEffect>				m_pBasicEffect;

	// ViewPort
	DirectX::SimpleMath::Matrix							m_viewPort;

	// 追尾カメラ
	std::unique_ptr<FollowCamera>						m_pFollowCamera;

	// カーソル
	std::unique_ptr<MouseCursor>						m_pCursor;

	// フロア
	std::unique_ptr<Floor>								m_pFloor;

	// 壁
	std::unique_ptr<Wall>								m_pWall;

	// プレイヤー
	std::unique_ptr<Player>								m_pPlayer;

	// エネミー
	std::unique_ptr<Enemy>								m_pEnemy;

	// 弾管理用
	std::unique_ptr<BulletManager>						m_pBulletManager;

	// 時間
	float												m_totalTime;

	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_textures[Texture::ALL];

	// 体力ゲージデフォルトサイズ
	float												m_defaultGaugeScaleX;

	// 現在の体力ゲージスケール
	float												m_currentGaugeScaleX;
	
	// 前の体力ゲージスケール
	float												m_prevGaugeScaleX;
	
	// じわじわ減少するゲージ
	float												m_lightGreenGaugeRate;
	bool												m_gaugeFlag;

	// 警告エフェクト
	std::unique_ptr<WarningEffect>						m_warningEffect;
};