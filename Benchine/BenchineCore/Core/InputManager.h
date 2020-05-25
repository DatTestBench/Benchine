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
	Released
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
	std::string_view actionId;
	InputState inputState;
	int keyCode; // Remapped to an SDL keycode
	int mouseCode;
	GamepadButton button;
	int controllerId;
	bool isActive;

	InputBinding(std::string_view id, InputState state, int keyCode = -1, int mouseCode = -1, GamepadButton button = MAX_BUTTONS, int controllerId = 0)
		: actionId(id)
		, inputState(state)
		, keyCode(keyCode - 61)
		, mouseCode(mouseCode)
		, button(button)
		, controllerId(controllerId)
		, isActive(false)
	{

	}

};

struct KeyEvent
{
	int keyCode;
	InputState state;
	bool processed;
	KeyEvent(int keyCode, InputState state)
		: keyCode(keyCode)
		, state(state)
		, processed(false)
	{

	}
};

struct Controller
{
	bool isConnected;
	bool buttons[MAX_BUTTONS];
};

class InputManager final : public Singleton<InputManager>
{
public:
	InputManager()
		: m_Controllers()
		, m_KeyEvents()
	{

	}

	bool AddInputBinding(InputBinding binding);
	bool IsBindingActive(std::string_view actionId);
	void LogKeyUp(SDL_Scancode key);
	void LogKeyDown(SDL_Scancode key);
	bool IsKeyDown(SDL_Scancode key);

	bool ProcessInput();
	bool IsPressed(GamepadButton button, int controllerId);
	std::tuple<int, int, Uint32> GetMouseState();


private:

	std::vector<KeyEvent> m_KeyEvents;
	bool m_Keys[512];

	Controller m_Controllers[XUSER_MAX_COUNT];

	std::map<std::string_view, InputBinding> m_InputBinds;

	void ClearInputs();
};


