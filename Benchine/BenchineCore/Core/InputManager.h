#pragma once
#include <XInput.h>
#include <bitset>
#include <map>
#include <tuple>
#include <vector>
#include <functional>
#include <string_view>
#include <functional>
#include "Helpers/Singleton.h"

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
	std::string_view actionId;
	std::function<void()> callBack;
	InputState inputState;
	int32_t keyCode; // Remapped to an SDL keycode
	int32_t mouseButton;
	GamepadButton padButton;
	int ControllerId;
	bool IsActive;

	explicit InputBinding(const std::string_view id, const std::function<void()> callBack, const InputState state, const int32_t  key = -1, const int32_t mouseCode = -1, const GamepadButton button = MAX_BUTTONS, const uint32_t gamepadId = 0)
		: actionId(id)
		, callBack(callBack)
		, inputState(state)
		, keyCode(SDL_GetScancodeFromKey(key))
		, mouseButton(mouseCode)
		, padButton(button)
		, ControllerId(gamepadId)
		, IsActive(false)
	{

	}
};

struct KeyEvent
{
	int32_t keyCode;
	InputState inputState;
	bool isProcessed;
	explicit KeyEvent(const int32_t code, const InputState state)
		: keyCode(code)
		, inputState(state)
		, isProcessed(false)
	{

	}
};

struct Controller
{
	bool isConnected;
	std::array<bool, MAX_BUTTONS> buttons;
	std::array<InputState, MAX_BUTTONS> buttonStates;
};

class InputManager final : public Singleton<InputManager>
{
public:
	explicit InputManager(token)
		: m_KeyEvents()
		, m_Controllers()
		, m_InputBinds()
	{

	}

	bool AddInputBinding(InputBinding binding);
	bool IsBindingActive(std::string_view actionId);

	bool ProcessInput();
	bool IsPressed(GamepadButton button, int controllerId);
	std::tuple<int, int, Uint32> GetMouseState();


private:

	void LogKeyPressed(SDL_Scancode key);
	void LogKeyReleased(SDL_Scancode key);
	std::vector<KeyEvent> m_KeyEvents;

	std::array<Controller, XUSER_MAX_COUNT> m_Controllers;
	
	std::multimap<std::string_view, InputBinding> m_InputBinds;

	void ClearInputs();
	void CheckControllerInput(DWORD index, XINPUT_STATE xInputState, GamepadButton button, int xInputConstant);
};


