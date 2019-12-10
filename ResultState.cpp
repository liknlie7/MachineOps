#include "pch.h"

#include "ResultState.h"

#include "DebugFont.h"
#include "GameContext.h"
#include "GameStateManager.h"


ResultState::ResultState()
	: GameState()
	, m_count(0)
{

}


ResultState::~ResultState()
{

}


void ResultState::Initialize()
{
	m_count = 0;
}


void ResultState::Update(float timer)
{
	m_count++;

	if (m_count > 120)
	{
		GameStateManager* gameStateManager = GameContext::Get<GameStateManager>();
		gameStateManager->RequestState("Title");
		m_count = 0;
	}

}


void ResultState::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 10, L"ResultState");
	debugFont->draw();
	debugFont->print(10, 40, L"%3d / 120", m_count);
	debugFont->draw();
}


void ResultState::Finalize()
{

}