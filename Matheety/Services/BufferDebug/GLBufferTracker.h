#pragma once
#include <vector>
#include <memory>
#include <string>
#include "imgui.h"
#include "GraphicDebugDefinitions.h"
#include "GraphicDebugWindow.h"
#include "GraphicStructs.h"

#ifdef GRAPHICS_DEBUG
class GLBufferTracker:public virtual GraphicDebugWindow
{

public:
    static GLBufferTracker* getInstance()
    {
        static GLBufferTracker instance;

        return &instance;
    }

    // Inherited via GraphicDebugWindow
    void Show() override;
    void UpdateBufferDisplay(const std::vector<Vertex>& vec);
    void UpdateBufferDisplay(const std::vector<int>& vec);
private:
    std::string m_vertexDataStr = "";
    std::string m_indexDataStr = "";
    ImGuiTextBuffer log;
    ImGuiTextBuffer log1;
private:
    GLBufferTracker() {}
public:
    GLBufferTracker(GLBufferTracker const&) = delete;
    void operator=(GLBufferTracker const&) = delete;

};
#endif