#include "BenchinePCH.h"
#include "Debugging/Logger.h"


void Logger::OutputLog()
{
	m_LogList.erase(std::remove_if(m_LogList.begin(), m_LogList.end(), [](const LogEntry& entry) { return entry.markedForClear; }), m_LogList.end());

	if (ImGui::Begin("Log"))
	{
		static LogLevel currentLevel = LEVEL_FULL;
		if (ImGui::BeginCombo("LevelSelection", m_LevelTags[m_CurrentLevel].c_str())) // Reference to implementation https://github.com/ocornut/imgui/issues/1658
		{
			for (int i = 0; i < IM_ARRAYSIZE(m_LevelTags); i++)
			{
				if (ImGui::Selectable(m_LevelTags[i].c_str(), m_CurrentLevel == i))
				{
					m_CurrentLevel = LogLevel(i);
				}
			}
			ImGui::EndCombo();
		}

		ImGui::SameLine();

		ImGui::Checkbox("Show Headers", &m_ShowHeaders);

		int logLine = 1;
		for (auto& log : m_LogList)
		{
			if (log.outputLocation == LOG_IMGUI)
			{
				if (log.level == m_CurrentLevel || m_CurrentLevel == LEVEL_FULL)
				{
					if (ImGui::SmallButton((std::to_string(logLine++) + "::").c_str()))
					{
						log.markedForClear = true;
					}

					ImGui::SameLine();

					if (m_ShowHeaders)
					{
						ImGui::TextColored(m_ImGuiColors[log.level], ("[" + m_LevelTags[log.level] + "] " + log.header + " > " + log.message.str()).c_str());
					}
					else
					{
						ImGui::LogText("");
						ImGui::TextColored(m_ImGuiColors[log.level], log.message.str().c_str());
					}
				}
			}
			if (log.outputLocation == LOG_CONSOLE)
			{
				// TODO: fix repeat console output
				std::cout << "[" + m_LevelTags[log.level] + "]" + log.header + " > " + log.message.str() << "\n";
			}
		}
	}
	ImGui::End();
}