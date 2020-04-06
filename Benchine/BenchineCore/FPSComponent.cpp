#include "BenchinePCH.h"
#include "FPSComponent.h"

FPSComponent::FPSComponent()
	: m_FPS()
{

}

void FPSComponent::Initialize()
{

}

void FPSComponent::Update(float dT)
{
	m_FPS = 1.f / dT;
}

void FPSComponent::Draw() const
{

}

float FPSComponent::GetFPS() const
{
	return m_FPS;
}