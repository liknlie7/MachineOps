#pragma once

#include "DeviceResources.h"
#include "WICTextureLoader.h" 
#include "GameContext.h"

// HPゲージ
class HPGauge
{
public: // 基本

	// コンストラクタ
	HPGauge();
	// デストラクタ
	~HPGauge();

public: // アクセサ

	// 体力の設定
	void SetLife(const float& _life)
	{
		m_life = _life;
	}
	
	// 体力の取得
	float GetLife() const
	{
		return m_life;
	}

	// 体力最大値の設定
	void SetMaxLife(const float& _maxLife)
	{
		m_maxLife = _maxLife;
	}


public: // 関数

	// 更新
	void Update();

	// 描画
	void Render();

private: // サブ関数

	// 線形補間
	float Lerp(float _start, float _end, float _time)
	{
		return _start + (_end - _start) * _time;
	}

private: // 定数

	// デフォルトXサイズ
	static const float DEFAULT_GAUGE_SCALE_X;

private: // 変数

	// 体力テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_greenHpBarTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_redHpBarTexture;

	// 体力
	float m_life;
	// 体力最大値
	float m_maxLife;
	// 体力ゲージデフォルトサイズ
	float m_defaultGaugeScaleX;
	// 現在の体力ゲージスケール
	float m_currentGaugeScaleX;
	// 前の体力ゲージスケール
	float m_prevGaugeScaleX;
	// じわじわ減少するゲージ
	float m_lightGreenGaugeRate;
	bool m_gaugeFlag;
	// 経過時間
	float												m_totalTime;

};

