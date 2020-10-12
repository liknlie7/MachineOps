#pragma once

#include <memory>
#include <CommonStates.h>
#include <SpriteBatch.h>
#include <SimpleMath.h>
#include <Effects.h>
#include <Keyboard.h>
#include <SpriteBatch.h>

#include "DeviceResources.h"
#include "GameContext.h"
#include "Projection.h"
#include "Keyboard.h"
#include "SceneManager.h"
#include "WICTextureLoader.h" 
#include "StepTimer.h"
#include "Adx2Le.h"

#include "DebugFont.h"
#include "DebugCamera.h"
#include "GridFloor.h"
#include "FollowCamera.h"
#include "Floor.h"
#include "Wall.h"
#include "Player.h"
#include "Enemy.h"
#include "Collision.h"
#include "MouseCursor.h"
#include "EffectMask.h"
#include "PlayerSound.h"
#include "PlaySceneSound.h"
#include "WarningEffect.h"
#include "BulletManager.h"
#include "Bullet.h"

// プレイシーンクラス
class PlayScene : public IScene
{
public:

	// ゲームステート
	enum GAME_STATE
	{
		STATE_START,		// ゲーム開始
		STATE_GAME,			// ゲーム中
		STATE_CONTINUE,		// 死んだので再チャレンジ
		STATE_NEXT,			// 次のウェーブへ
		STATE_GAMEOVERA,	// ゲームオーバー
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

public: // アクセッサ

	// カメラの取得
	FollowCamera* GetCamera()
	{
		return m_pFollowCamera.get();
	}

	// エフェクト用ベーシックエフェクトを取得する関数
	DirectX::BasicEffect* GetBatchEffect()
	{
		return m_batchEffect.get();
	}

	// エフェクト用プリミティブバッチを取得する関数
	DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>* GetPrimitiveBatch()
	{
		return m_primitiveBatch.get();
	}

	// エフェクト用入力レイアウトを取得する関数
	ID3D11InputLayout* GetInputLayout()
	{
		return m_inputLayout.Get();
	}

public: // 関数

	// 初期化
	eScene Initialize() override;

	// 更新
	eScene Update(DX::StepTimer const& _timer) override;
	
	// 描画
	eScene Render() override;
	
	// 後始末
	eScene Finalize() override;

	// ゲームの初期化
	GAME_STATE InitializeGame();

	// ゲームをスタート
	GAME_STATE StartGame();

	// ゲーム中
	GAME_STATE PlayGame();

	// コンティニュー
	GAME_STATE ContinueGame();

	// 次のウェーブへ
	GAME_STATE NextWave();

private: // サブ関数

	// 線形補間
	float Lerp(float _start, float _end, float _time);

	// 球面線形補間
	float Slerp(float _start, float _end, float _time);

private: // 定数

	static const float DAMAGE_TIME;

private: // 変数

	// サウンド
	std::weak_ptr<Adx2Le>						m_pSound;

	//----- エフェクト用 -----//
	// エフェクト
	std::unique_ptr<DirectX::BasicEffect> m_batchEffect;
	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_primitiveBatch;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
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

	// 敵
	std::unique_ptr<Enemy>								m_pEnemy;
	std::unique_ptr<Enemy>								m_pEnemies[4];
	bool bossFlag;

	// 弾管理用
	//std::unique_ptr<BulletManager>						m_pBulletManager;

	// 色
	DirectX::SimpleMath::Color							m_color;

	// 時間
	float												m_totalTime;

	// 体力テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_greenHpBarTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_redHpBarTexture;

	// 体力ゲージデフォルトサイズ
	float m_defaultGaugeScaleX;
	// 現在の体力ゲージスケール
	float m_currentGaugeScaleX;
	// 前の体力ゲージスケール
	float m_prevGaugeScaleX;
	// じわじわ減少するゲージ
	float m_lightGreenGaugeRate;
	bool m_gaugeFlag;

	// 警告エフェクト
	std::unique_ptr<WarningEffect>						m_warningEffect;

	// ウェーブカウント
	int m_waveCount;
};