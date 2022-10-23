#include "GraphicDebugWindows.h"

#ifdef GRAPHICS_DEBUG
GraphicDebugWindows::GraphicDebugWindows()
{
	m_windows.push_back(GLBufferTracker::getInstance());
}

void GraphicDebugWindows::ShowWindows()
{
	for (auto& win : m_windows)
	{
		win->Show();
	}
}





#endif