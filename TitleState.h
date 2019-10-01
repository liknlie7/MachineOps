#pragma once

#include "GameState.h"

class TitleState : public GameState
{
private:

	int m_count;

public:

	TitleState();
	virtual ~TitleState();

public:

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Finalize() override;
};