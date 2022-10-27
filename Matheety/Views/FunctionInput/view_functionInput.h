#pragma once
#include <iostream>
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <Services/Helpers/Event.h>

class view_functionInput
{
public:
	view_functionInput();
	~view_functionInput();
	void Show();
	

	struct Events
	{
		Event<const std::string&> btn_click_run;
		Event<bool> dispose;
		friend view_functionInput;

	}events;


	struct Properties
	{
		std::string GetFuncText();
	private:
		char m_funcText[1024 * 16] = "";
		friend view_functionInput;
	}props;

};