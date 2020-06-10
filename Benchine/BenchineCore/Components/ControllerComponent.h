#pragma once
#include "Components/BaseComponent.h"

class ControllerComponent final : public BaseComponent
{
public:
	ControllerComponent();
	virtual ~ControllerComponent() override = default;
	DEL_ROF(ControllerComponent);

	void Update(float dT) override;

	

protected:
	void Initialize() override;

private:
};