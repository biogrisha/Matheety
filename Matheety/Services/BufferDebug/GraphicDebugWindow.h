#pragma once
#include "GraphicDebugDefinitions.h"

#ifdef GRAPHICS_DEBUG
class GraphicDebugWindow
{
public:
	virtual~GraphicDebugWindow() = default;
	virtual void Show() = 0;
};
#endif