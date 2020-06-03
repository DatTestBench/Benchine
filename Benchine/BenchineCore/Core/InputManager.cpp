#include "BenchinePCH.h"
#include "Core/InputManager.h"

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
			LogKeyDown(e.key.keysym.scancode);
		}
		if (e.type == SDL_KEYUP)
		{
			LogKeyUp(e.key.keysym.scancode);
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
	DWORD dwResult;

	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		// Get the state of the controller
		dwResult = XInputGetState(i, &state);
		if (dwResult == ERROR_SUCCESS && !m_Controllers.at(i).isConnected)
		{
			// Controller Connected
			m_Controllers.at(i).isConnected = true;
			Logger::Log<LEVEL_DEBUG>("InputManager::ProcessInput()") << "Controller Connected";


		}
		else if (dwResult != ERROR_SUCCESS && m_Controllers[i].isConnected)
		{
			// Controller Disconnected
			m_Controllers.at(i).isConnected = false;
			Logger::Log<LEVEL_DEBUG>("InputManager::ProcessInput()") << "Controller Disconnected";

		}

		// Bind all inputs to each controller
		m_Controllers.at(i).buttons.at(GamepadButton::DPAD_UP) = state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
		m_Controllers.at(i).buttons.at(GamepadButton::DPAD_DOWN) = state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
		m_Controllers.at(i).buttons.at(GamepadButton::DPAD_LEFT) = state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
		m_Controllers.at(i).buttons.at(GamepadButton::DPAD_RIGHT) = state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
		m_Controllers.at(i).buttons.at(GamepadButton::START) = state.Gamepad.wButtons & XINPUT_GAMEPAD_START;
		m_Controllers.at(i).buttons.at(GamepadButton::BACK) = state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK;
		m_Controllers.at(i).buttons.at(GamepadButton::LEFT_THUMB) = state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB;
		m_Controllers.at(i).buttons.at(GamepadButton::RIGHT_THUMB) = state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB;
		m_Controllers.at(i).buttons.at(GamepadButton::LEFT_SHOULDER) = state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
		m_Controllers.at(i).buttons.at(GamepadButton::RIGHT_SHOULDER) = state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
		m_Controllers.at(i).buttons.at(GamepadButton::A) = state.Gamepad.wButtons & XINPUT_GAMEPAD_A;
		m_Controllers.at(i).buttons.at(GamepadButton::B) = state.Gamepad.wButtons & XINPUT_GAMEPAD_B;
		m_Controllers.at(i).buttons.at(GamepadButton::X) = state.Gamepad.wButtons & XINPUT_GAMEPAD_X;
		m_Controllers.at(i).buttons.at(GamepadButton::Y) = state.Gamepad.wButtons & XINPUT_GAMEPAD_Y;

	}

	int mouseX, mouseY;
	const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

	io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
	io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
	io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
	io.MouseWheel = static_cast<float>(wheel);



	for (auto& bind : m_InputBinds)
	{
		// Keyboard Checks
		bool keyBoardActive = false;
		for (auto& keyEvent : m_KeyEvents)
		{
			if (keyEvent.keyCode == bind.second.keyCode && keyEvent.state == bind.second.inputState)
			{
				keyBoardActive = true;
				keyEvent.processed = true;
			}
		}

		// XINPUT Checks
		bool controllerActive = false;
		if (m_Controllers.at(bind.second.controllerId).buttons.at(bind.second.button))
		{
			controllerActive = true;
		}

		bind.second.isActive = keyBoardActive || controllerActive;
	}

	return false;
}


bool InputManager::AddInputBinding(InputBinding binding)
{
	size_t oldSize = m_InputBinds.size();
	m_InputBinds.try_emplace(binding.actionId, binding);
	size_t newSize = m_InputBinds.size();

	if (oldSize == newSize)
	{
		Logger::Log<LEVEL_WARNING>("InputManager::AddInputBinding()") << "Input with ID " << binding.actionId << " already exists";
		return false;
	}
	return true;
}

bool InputManager::IsBindingActive(std::string_view actionId)
{
	return m_InputBinds.at(actionId).isActive;
}

bool InputManager::IsPressed(GamepadButton button, int controllerId)
{

	if (m_Controllers.at(controllerId).isConnected)
	{
		return m_Controllers.at(controllerId).buttons[button];
	}
	return false;
}

void InputManager::LogKeyDown(SDL_Scancode key)
{
	m_KeyEvents.emplace_back(KeyEvent(key, InputState::Pressed));
}

void InputManager::LogKeyUp(SDL_Scancode key)
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
	m_KeyEvents.erase(std::remove_if(m_KeyEvents.begin(), m_KeyEvents.end(), [](const KeyEvent& keyEvent) { return keyEvent.processed; }), m_KeyEvents.end());
}