#include "pch.h"

#include <cassert>

#include "GameStateManager.h"
#include "GameState.h"


GameStateManager::GameStateManager()
	: m_stateFactories()
	, m_activeState(nullptr)
	, m_nextStateName()
{
}


GameStateManager::~GameStateManager()
{
}


void GameStateManager::SetStartState(const std::string& stateName)
{
	RequestState(stateName);
}


void GameStateManager::Update()
{
	if (!m_nextStateName.empty())
	{
		ChangeState();
	}

	assert(m_activeState && "There is no active state.");
	m_activeState->Update();
}


void GameStateManager::Render()
{
	assert(m_activeState && "There is no active state.");
	m_activeState->Render();
}


void GameStateManager::RequestState(const std::string& stateName)
{
	assert(m_stateFactories.count(stateName) == 1 && "A GameState with this name is not registered.");

	m_nextStateName = stateName;
}


void GameStateManager::ChangeState()
{
	if (m_activeState)
	{
		m_activeState->Finalize();
	}

	m_activeState = m_stateFactories[m_nextStateName]();
	m_activeState->Initialize();

	m_nextStateName.clear();
}