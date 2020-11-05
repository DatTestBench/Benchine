#include "BenchinePCH.h"
#include "Core/InputManager.h"
#include <future>

bool InputManager::ProcessInput()
{

	ImGuiIO& io = ImGui::GetIO();
	int wheel = 0;
	ClearInputs();

	// SDL
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			return true;
		}
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			LogKeyPressed(e.key.keysym.scancode);
		}
		if (e.type == SDL_KEYUP)
		{
			LogKeyReleased(e.key.keysym.scancode);
		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{

		}
		if (e.type == SDL_WINDOWEVENT)
		{
			if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				io.DisplaySize.x = static_cast<float>(e.window.data1);
				io.DisplaySize.y = static_cast<float>(e.window.data2);
			}
		}
		if (e.type == SDL_MOUSEWHEEL)
		{
			wheel = e.wheel.y;
		}
	}

	// XINPUT https://docs.microsoft.com/en-us/windows/win32/xinput/getting-started-with-xinput
	DWORD dwResult{};

	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		// Get the state of the controller
		dwResult = XInputGetState(i, &state); // TODO: This thing is awfully slow, find a way to not have to recheck it every frame;
		if (dwResult == ERROR_SUCCESS && !m_Controllers.at(i).isConnected)
		{
			// Controller Connected
			m_Controllers.at(i).isConnected = true;
			DEBUGONLY(Logger::Log<LEVEL_DEBUG>("InputManager::ProcessInput()") << "Controller Connected");


		}
		else if (dwResult != ERROR_SUCCESS && m_Controllers[i].isConnected)
		{
			// Controller Disconnected
			m_Controllers.at(i).isConnected = false;
			DEBUGONLY(Logger::Log<LEVEL_DEBUG>("InputManager::ProcessInput()") << "Controller Disconnected");

		}
		// Bind all inputs to each controller

		
		CheckControllerInput(i, state, GamepadButton::DPAD_UP, XINPUT_GAMEPAD_DPAD_UP);
		CheckControllerInput(i, state, GamepadButton::DPAD_DOWN, XINPUT_GAMEPAD_DPAD_DOWN);
		CheckControllerInput(i, state, GamepadButton::DPAD_LEFT, XINPUT_GAMEPAD_DPAD_LEFT);
		CheckControllerInput(i, state, GamepadButton::DPAD_RIGHT, XINPUT_GAMEPAD_DPAD_RIGHT);
		CheckControllerInput(i, state, GamepadButton::START, XINPUT_GAMEPAD_START);
		CheckControllerInput(i, state, GamepadButton::BACK, XINPUT_GAMEPAD_BACK);
		CheckControllerInput(i, state, GamepadButton::LEFT_THUMB, XINPUT_GAMEPAD_LEFT_THUMB);
		CheckControllerInput(i, state, GamepadButton::RIGHT_THUMB, XINPUT_GAMEPAD_RIGHT_THUMB);
		CheckControllerInput(i, state, GamepadButton::LEFT_SHOULDER, XINPUT_GAMEPAD_LEFT_SHOULDER);
		CheckControllerInput(i, state, GamepadButton::RIGHT_SHOULDER, XINPUT_GAMEPAD_RIGHT_SHOULDER);
		CheckControllerInput(i, state, GamepadButton::A, XINPUT_GAMEPAD_A);
		CheckControllerInput(i, state, GamepadButton::B, XINPUT_GAMEPAD_B);
		CheckControllerInput(i, state, GamepadButton::X, XINPUT_GAMEPAD_X);
		CheckControllerInput(i, state, GamepadButton::Y, XINPUT_GAMEPAD_Y);

	}

	int mouseX, mouseY;
	const auto buttons = SDL_GetMouseState(&mouseX, &mouseY);

	io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
	io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
	io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
	io.MouseWheel = static_cast<float>(wheel);



	for (auto& bind : m_InputBinds)
	{
		// Keyboard Checks
		bool keyBoardActive = false;

		if (bind.second.inputState == InputState::Down)
		{
			const Uint8* state = SDL_GetKeyboardState(NULL);
			if (state[bind.second.keyCode])
			{
				//auto a = std::async(bind.second.CallBack);
				bind.second.callBack();
				keyBoardActive = true;
			}
		}
		else
		{
			for (auto& keyEvent : m_KeyEvents)
			{
				if (keyEvent.keyCode == bind.second.keyCode && keyEvent.inputState == bind.second.inputState)
				{
					//auto a = std::async(bind.second.CallBack);
					bind.second.callBack();
					keyBoardActive = true;
					keyEvent.isProcessed = true;
				}
			}
		}

		// XINPUT Checks
		bool controllerActive = false;
		if (bind.second.padButton != GamepadButton::MAX_BUTTONS)
		{
			if (m_Controllers.at(static_cast<uint32_t>(bind.second.ControllerId)).buttons.at(bind.second.padButton) 
				&& (m_Controllers.at(static_cast<uint32_t>(bind.second.ControllerId)).buttonStates.at(bind.second.padButton) == bind.second.inputState))
			{
				//auto a = std::async(bind.second.CallBack);
				bind.second.callBack();
				controllerActive = true;
			}
		}
		bind.second.IsActive = keyBoardActive || controllerActive;
	}

	return false;
}




bool InputManager::AddInputBinding(InputBinding binding)
{
	size_t oldSize = m_InputBinds.size();
	m_InputBinds.emplace(binding.actionId, binding);
	size_t newSize = m_InputBinds.size();

	if (oldSize == newSize)
	{
		DEBUGONLY(Logger::Log<LEVEL_WARNING>("InputManager::AddInputBinding()") << "Input with ID " << binding.actionId << " already exists");
		return false;
	}
	return true;
}

bool InputManager::IsBindingActive(std::string_view)
{
	return true;
	//return m_InputBinds.at(actionId).IsActive;
}

bool InputManager::IsPressed(GamepadButton button, int controllerId)
{

	if (m_Controllers.at(static_cast<uint32_t>(controllerId)).isConnected)
	{
		return m_Controllers.at(static_cast<uint32_t>(controllerId)).buttons[button];
	}
	return false;
}

void InputManager::LogKeyPressed(SDL_Scancode key)
{
	m_KeyEvents.emplace_back(KeyEvent(key, InputState::Pressed));
}
void InputManager::LogKeyReleased(SDL_Scancode key)
{
	m_KeyEvents.emplace_back(KeyEvent(key, InputState::Released));
}


std::tuple<int, int, Uint32> InputManager::GetMouseState()
{
	int x, y;
	Uint32 mouseState = SDL_GetMouseState(&x, &y);
	return std::tuple<int, int, Uint32>(x, y, mouseState);
}

void InputManager::ClearInputs()
{
	m_KeyEvents.erase(std::remove_if(m_KeyEvents.begin(), m_KeyEvents.end(), [](const KeyEvent& keyEvent) { return keyEvent.isProcessed; }), m_KeyEvents.end());
}

void InputManager::CheckControllerInput(DWORD index, XINPUT_STATE xinputstate, GamepadButton button, int xinputconstant)
{
	bool previous = m_Controllers.at(index).buttons.at(button);
	if (xinputstate.Gamepad.wButtons & xinputconstant)
	{
		m_Controllers.at(index).buttons.at(button) = true;
		m_Controllers.at(index).buttonStates.at(button) = previous ? InputState::Down : InputState::Pressed;
	}
	else
	{
		m_Controllers.at(index).buttons.at(button) = false;
	}
}