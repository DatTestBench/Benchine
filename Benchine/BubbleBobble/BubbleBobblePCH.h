#pragma once

// STL
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <map>
#include <functional>
#include <chrono>
#include <thread>
#include <algorithm>
#include <string_view>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

// IMGUI
#pragma warning (push, 0)
#include "ImGui/imgui.h"
#include "ImGui/imgui_sdl.h"
#pragma warning (pop)
// SDL
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>


// Macros
#define DEL_ROF(className) \
className(const className&) = delete; \
className(className&&) noexcept = delete; \
className& operator= (const className&) = delete; \
className& operator= (className&&) noexcept = delete;

#define UNUSED(var) var;

// Functions
template<class T>
inline void SafeDelete(T& pObject)
{
	if (pObject != nullptr)
	{
		delete pObject;
		pObject = nullptr;
	}
}

// General Includes
#include "Resources//ResourceManager.h"
#include "Graphics/Renderer.h"
#include "Core/InputManager.h"
#include "Scene/SceneManager.h"
#include "Debugging/Logger.h"