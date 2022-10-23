#include "GLBufferTracker.h"
#ifdef GRAPHICS_DEBUG
void GLBufferTracker::Show()
{
	ImGui::Begin("GLBufferTracker");
	ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
	if (ImGui::BeginTabBar("GLBufferTabBar", tab_bar_flags))
	{
		if (ImGui::BeginTabItem("Vertex Buffer"))
		{
			ImGui::TextUnformatted(log.begin(), log.end());
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Index Buffer"))
		{
			ImGui::TextUnformatted(log1.begin(), log1.end());
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	ImGui::End();
}

void GLBufferTracker::UpdateBufferDisplay(const std::vector<Vertex>& vec)
{
	m_vertexDataStr.clear();
	int i = 0;
	for (auto& el : vec)
	{
		m_vertexDataStr += std::to_string(i)+". " + std::to_string(el.pos.x) + " "
			+ std::to_string(el.pos.y) + " "
			+ std::to_string(el.pos.z) + " "
			+ std::to_string(el.pos.w) + " "
			+ std::to_string(el.col.r) + " "
			+ std::to_string(el.col.g) + " "
			+ std::to_string(el.col.b) + " "
			+ std::to_string(el.col.a) + "\n";
		i++;
	}
	log.clear();
	log.appendf(m_vertexDataStr.c_str());
}

void GLBufferTracker::UpdateBufferDisplay(const std::vector<int>& vec)
{
	m_indexDataStr.clear();
	int i = 0;
	for (auto& el : vec)
	{
		m_indexDataStr += std::to_string(i) + ". " + std::to_string(el) + "\n";
		i++;
	}
	log1.clear();
	log1.appendf(m_indexDataStr.c_str());
}
#endif

