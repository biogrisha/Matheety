#pragma once
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glad/glad.h>

class view_renderSpace
{
public:
	view_renderSpace();
	void Show();
	void SetRenderTarget(GLuint renderTarget)
	{
		m_renderTarget = renderTarget;
	}

private:
	GLuint m_renderTarget;
};