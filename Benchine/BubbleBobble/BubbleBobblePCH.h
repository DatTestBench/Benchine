#pragma once

// STL
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <chrono>
#include <thread>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// SDL
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

// IMGUI
#include "imgui.h"
#include "imgui_sdl.h"

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