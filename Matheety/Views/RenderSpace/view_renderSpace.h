#pragma once
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <Services/Helpers/Event.h>
#include <Services/Helpers/Helpers.h>

class view_renderSpace
{
public:
	view_renderSpace();
	void Show();
	void SetRenderTarget(GLuint renderTarget)
	{
		m_renderTarget = renderTarget;
	}

	struct {
		Event<float, float> onMouseDrag;
		Event<float> onWKey;
		Event<float> onSKey;
		Event<float> onAKey;
		Event<float> onDKey;
	}events;
private:
	struct {
		bool isDragged = false;
		ImVec2 posClick;
		ImVec2 posRelease;
	}m_navigation;

	GLuint m_renderTarget;
};