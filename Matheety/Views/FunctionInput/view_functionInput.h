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
		Event<float> rangeChanged;
		friend view_functionInput;

	}events;


	struct Properties
	{
		std::string GetFuncText();
	private:
		char m_funcText[1024 * 16] = "return x*y;";

		bool m_isSliderDragged = false;
		float m_rangeFrom = 0.1;
		float m_rangeTo = 10;
		float m_ramgeVal = 0;
		friend view_functionInput;
	}props;

};