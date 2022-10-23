#pragma once
#include <vector>
#include <memory>
#include "GraphicDebugDefinitions.h"
#include "GraphicDebugWindow.h"
#include "GLBufferTracker.h"
#ifdef GRAPHICS_DEBUG

class GraphicDebugWindows
{
public:
	GraphicDebugWindows();
	void ShowWindows();
private:
	std::vector<GraphicDebugWindow*> m_windows;
};
#endif