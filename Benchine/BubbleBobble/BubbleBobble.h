#pragma once
#include "Core/BaseGame.h"
class BubbleBobble final : public BaseGame
{
public:
	BubbleBobble() = default;
	virtual ~BubbleBobble() override = default;
	DEL_ROF(BubbleBobble)

protected:
	void Initialize() override;
	void Update([[maybe_unused]] float dT) override;
};