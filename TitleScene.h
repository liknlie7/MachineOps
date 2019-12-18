#pragma once

#include "GameScene.h"
#include "DeviceResources.h"

#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <Keyboard.h>
#include <CommonStates.h>

#include "StepTimer.h"

class TitleScene : public GameScene
{
public:

	TitleScene();
	virtual ~TitleScene();

public:

	void Initialize() override;
	void Update(DX::StepTimer const& timer) override;
	void Render() override;
	void Finalize() override;

private:

	std::unique_ptr<DirectX::SpriteBatch>	m_spriteBatch;
	std::unique_ptr<DirectX::SpriteFont>	m_spriteFont;

	DirectX::SimpleMath::Vector4 color;
	float alpha;
	bool fadeFlag;
};