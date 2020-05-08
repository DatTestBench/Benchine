#pragma once
#include "Core/BaseGame.h"
class BubbleBobble final : public BaseGame
{
public:
	BubbleBobble() = default;
	virtual ~BubbleBobble() = default;
	DEL_ROF(BubbleBobble);

protected:
	void Initialize() override;
	void Update(float dT) override;
	void Draw() const override;
};