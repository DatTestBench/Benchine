#pragma once
// Using a basegame so the engine can be reused for games other than BubbleBobble without having to rewrite the Runner
class BaseGame
{
public:
	BaseGame() = default;
	virtual ~BaseGame() = default;
	DEL_ROF(BaseGame);


	void BaseInitialize();
	void BaseUpdate(float dT);
	void BaseDraw() const;

protected:
	virtual void Initialize() = 0;
	virtual void Update(float dT) = 0;
	virtual void Draw() const = 0;
private:
	std::string m_Name;
};