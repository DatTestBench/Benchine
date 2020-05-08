#pragma once

#include "Helpers/Singleton.h"
#include "ImGui/imgui.h"

#include <string_view>
#include <string>
#include <vector>
#include <array>
#include <sstream>

enum LogLevel : int
{
	LEVEL_DEBUG,
	LEVEL_INFO,
	LEVEL_WARNING,
	LEVEL_ERROR,
	LEVEL_FULL
};

enum LogArgument : int
{
	LOG_IMGUI,
	LOG_CONSOLE
};

struct LogEntry
{
	std::string header;
	std::stringstream message;
	LogLevel level;
	LogArgument outputLocation;
	bool markedForClear;
	LogEntry(const std::string& log, LogLevel level, LogArgument outputLocation)
		: header(log)
		, level(level)
		, outputLocation(outputLocation)
		, markedForClear(false)

	{
	}
};

class Logger : public Singleton<Logger>
{
public:
	template<LogLevel level, LogArgument outputLocation = LogArgument::LOG_IMGUI>
	static Logger& Log(const std::string& header = "")
	{
		static_assert(level != LEVEL_FULL, "LEVEL_FULL is not a valid LogLevel");

		GetInstance()->m_LogList.push_back(LogEntry(header, level, outputLocation));
		return *GetInstance();
	}

	template<class T>
	Logger& operator<<(const T& log)
	{
		m_LogList.back().message << log;
		return *GetInstance();
	}

	void OutputLog();

private:
	std::vector<LogEntry> m_LogList;
	bool m_ShowHeaders = true;
	LogLevel m_CurrentLevel = LEVEL_FULL;

	const ImVec4 m_ImGuiColors[5]
	{
		{ 1.f, 0.f, 1.f, 1.f }, // DEBUG
		{ 1.f, 1.f, 1.f, 1.f }, // INFO
		{ 1.f, 1.f, 0.f, 1.f }, // WARNING
		{ 1.f, 0.f, 0.f, 1.f },	// ERROR
		{ 1.f, 1.f, 1.f, 1.f }	// DEFAULT
	};

	const std::string m_LevelTags[5]
	{
		"DEBUG",
		"INFO",
		"WARNING",
		"ERROR",
		"FULL" // Only used to for displaying in the log window, should not be passed to logentries
	};
};