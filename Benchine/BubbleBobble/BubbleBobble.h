#pragma once
#include "BaseGame.h"
class BubbleBobble final : public BaseGame
{
protected:
	void Initialize() override;
	void Update(float dT) override;
	void Draw() const override;
};