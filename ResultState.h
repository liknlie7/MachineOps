#pragma once

#include "GameState.h"
#include "DeviceResources.h"

#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <Keyboard.h>
#include <CommonStates.h>

class ResultState : public GameState
{
public:

	ResultState();
	virtual ~ResultState();

public:

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Finalize() override;

private:

	std::unique_ptr<DirectX::SpriteBatch>	m_spriteBatch;
	std::unique_ptr<DirectX::SpriteFont>	m_spriteFont;

};