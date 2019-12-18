#pragma once

#include "GameScene.h"
#include "DeviceResources.h"

#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <Keyboard.h>
#include <CommonStates.h>

#include "StepTimer.h"

class ResultScene : public GameScene
{
public:

	ResultScene();
	virtual ~ResultScene();

public:

	void Initialize() override;
	void Update(DX::StepTimer const& timer) override;
	void Render() override;
	void Finalize() override;

private:

	std::unique_ptr<DirectX::SpriteBatch>	m_spriteBatch;
	std::unique_ptr<DirectX::SpriteFont>	m_spriteFont;

};