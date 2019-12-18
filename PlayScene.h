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
#include "GameScene.h"
#include "Projection.h"
#include "Keyboard.h"
#include "GameSceneManager.h"
#include "WICTextureLoader.h" 
#include "StepTimer.h"

#include "DebugFont.h"
#include "DebugCamera.h"
#include "GridFloor.h"
#include "FollowCamera.h"
#include "Floor.h"
#include "Player.h"
#include "Enemy.h"
#include "Collision.h"

// プレイシーンクラス
class PlayScene : public GameScene
{
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
	void Finalize() override;

	float Lerp(float _start, float _end, float _time);

private: // 定数

	static const float DAMAGE_TIME;

private: // 変数

	// エフェクト
	std::unique_ptr<DirectX::BasicEffect>				m_pBasicEffect;

	// ViewPort
	DirectX::SimpleMath::Matrix							m_viewPort;

	// 追尾カメラ
	std::unique_ptr<FollowCamera>						m_pFollowCamera;

	// フロア
	std::unique_ptr<Floor>								m_pFloor;

	// プレイヤー
	std::unique_ptr<Player>								m_pPlayer;

	// 敵
	std::unique_ptr<Enemy>								m_pEnemy;

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

	std::unique_ptr<DirectX::GeometricPrimitive> geo;
	DirectX::SimpleMath::Matrix geoMat;
	DirectX::SimpleMath::Vector3 geoVec;
};