#include "view_functionInput.h"

view_functionInput::view_functionInput()
{

}

view_functionInput::~view_functionInput()
{
	events.dispose(true);
}

void view_functionInput::Show()
{
	ImGui::Begin("FunctionInput");
	ImGui::InputTextMultiline("##source", props.m_funcText, IM_ARRAYSIZE(props.m_funcText));
	if (ImGui::Button("Run"))
	{
		events.btn_click_run(props.GetFuncText());
	}

	ImGui::Text("Set Range:");

	if (ImGui::SliderScalar("slider float low", ImGuiDataType_Float, &(props.m_ramgeVal), &(props.m_rangeFrom), &(props.m_rangeTo)))
	{

		props.m_isSliderDragged = true;
	}
	if (ImGui::IsMouseReleased(ImGuiMouseButton_Left) && props.m_isSliderDragged)
	{
		props.m_isSliderDragged = false;
		events.rangeChanged(props.m_ramgeVal);

	}
	

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::End();
}

std::string view_functionInput::Properties::GetFuncText()
{
	return std::string(m_funcText);
}


