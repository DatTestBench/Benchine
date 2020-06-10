#pragma once
#include <XInput.h>
#include <bitset>
#include "Helpers/Singleton.h"
#include <map>
#include <tuple>
#include <vector>
#include <functional>
#include <string_view>

enum InputState
{
	Pressed,
	Released,
	Down
};

enum GamepadButton : uint16_t
{
	DPAD_UP,
	DPAD_DOWN,
	DPAD_LEFT,
	DPAD_RIGHT,
	START,
	BACK,
	LEFT_THUMB,
	RIGHT_THUMB,
	LEFT_SHOULDER,
	RIGHT_SHOULDER,
	A,
	B,
	X,
	Y,
	MAX_BUTTONS
};
struct InputBinding
{
	std::string_view ActionId;
	InputState State;
	int KeyCode; // Remapped to an SDL keycode
	int MouseCode;
	GamepadButton Button;
	int ControllerId;
	bool IsActive;

	InputBinding(std::string_view id, InputState state, int keyCode = -1, int mouseCode = -1, GamepadButton button = MAX_BUTTONS, int controllerId = 0)
		: ActionId(id)
		, State(state)
		, KeyCode(keyCode - 61)
		, MouseCode(mouseCode)
		, Button(button)
		, ControllerId(controllerId)
		, IsActive(false)
	{

	}

};

struct KeyEvent
{
	int KeyCode;
	InputState State;
	bool Processed;
	KeyEvent(int keyCode, InputState state)
		: KeyCode(keyCode)
		, State(state)
		, Processed(false)
	{

	}
};

struct Controller
{
	bool isConnected;
	std::array<bool, MAX_BUTTONS> buttons;
};

class InputManager final : public Singleton<InputManager>
{
public:
	InputManager(token)
		: m_KeyEvents()
		, m_Controllers()
		, m_InputBinds()
	{

	}

	bool AddInputBinding(InputBinding binding);
	bool IsBindingActive(std::string_view actionId);
	bool IsKeyDown(SDL_Scancode key);

	bool ProcessInput();
	bool IsPressed(GamepadButton button, int controllerId);
	std::tuple<int, int, Uint32> GetMouseState();


private:

	void LogKeyPressed(SDL_Scancode key);
	void LogKeyReleased(SDL_Scancode key);
	std::vector<KeyEvent> m_KeyEvents;
	//bool m_Keys[512];

	std::array<Controller, XUSER_MAX_COUNT> m_Controllers;

	std::map<std::string_view, InputBinding> m_InputBinds;

	void ClearInputs();
};


