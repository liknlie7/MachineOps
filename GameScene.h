#pragma once

#include "StepTimer.h"

class GameScene
{
public:

	GameScene() = default;

public:

	virtual ~GameScene() = default;

public:

	virtual void Initialize() = 0;
	virtual void Update(DX::StepTimer const& timer) = 0;
	virtual void Render() = 0;
	virtual void Finalize() = 0;
};