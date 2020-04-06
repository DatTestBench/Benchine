#pragma once
#include "BaseComponent.h"
class FPSComponent : public BaseComponent
{
public:
	FPSComponent();
	virtual ~FPSComponent() = default;
	DEL_ROF(FPSComponent);

	void Update(float dT) override;
	void Draw() const override;

	float GetFPS() const;

protected:
	void Initialize() override;

private:
	float m_FPS;
};

