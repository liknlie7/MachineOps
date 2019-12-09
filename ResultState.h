#pragma once

#include "GameState.h"

class ResultState : public GameState
{
private:

	int m_count;

public:

	ResultState();
	virtual ~ResultState();

public:

	void Initialize() override;
	void Update(DX::StepTimer const& timer) override;
	void Render() override;
	void Finalize() override;
};