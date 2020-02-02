#pragma once

#include "GameScene.h"
#include "DeviceResources.h"

#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <Keyboard.h>
#include <CommonStates.h>
#include <WICTextureLoader.h>

#include "StepTimer.h"
#include "GameContext.h"
#include "EffectManager.h"

class TitleScene : public GameScene
{
public:

	TitleScene();
	virtual ~TitleScene();

public:

	void Initialize() override;
	void Update(DX::StepTimer const& _timer) override;
	void Render() override;
	void Finalize() override;

private:

	std::unique_ptr<DirectX::SpriteBatch>	m_spriteBatch;
	std::unique_ptr<DirectX::SpriteFont>	m_spriteFont;

	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_titleTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_backGroundTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_massageTexture;

	// キーボードトラッカー
	DirectX::Keyboard::KeyboardStateTracker*				m_keyboardTracker;

	float m_time;

	DirectX::SimpleMath::Vector4 color;
	float alpha;
	bool fadeFlag;
};