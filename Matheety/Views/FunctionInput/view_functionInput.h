#pragma once
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <Application/Events.h>
class view_functionInput
{
public:
	view_functionInput(EventDispatcher* eventDisp);
	void Show();
	
private:

	char m_funcText[1024 * 16];

	//Events
	void InitEvents(EventDispatcher* eventDisp);
	Event<const std::string&>* m_e_SubmitFunction = nullptr;
	Event<bool>* m_e_RightRot = nullptr;
	Event<bool>* m_e_LeftRot  = nullptr;

};