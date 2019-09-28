#pragma once

#include <Model.h>
#include <Effects.h>
#include <CommonStates.h>

#include "DeviceResources.h"
#include "SimpleMath.h"
#include "Projection.h"
#include "GameContext.h"

class Floor
{
public:

	Floor() {}
	~Floor() {}

public:

	void Initialize();
	void Render(DirectX::SimpleMath::Matrix _view);

private:

	// ƒ‚ƒfƒ‹
	std::unique_ptr<DirectX::Model>	m_pModel;
};