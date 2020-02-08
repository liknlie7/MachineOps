#include "pch.h"
#include "WarningEffect.h"

WarningEffect::WarningEffect()
{
	m_pLine = std::make_unique<WarningLine>();
}

void WarningEffect::Initialize()
{
	m_pLine->Initialize();
}

void WarningEffect::Update(float _elapsedTime)
{
	m_pLine->Update(_elapsedTime);
}

void WarningEffect::Render()
{
	m_pLine->Render();
}