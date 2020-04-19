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

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

// IMGUI
#include "imgui.h"
#include "imgui_sdl.h"

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
#include "ResourceManager.h"
#include "Renderer.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Logger.h"