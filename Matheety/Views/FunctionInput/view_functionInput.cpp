#include "view_functionInput.h"

view_functionInput::view_functionInput(EventDispatcher* eventDisp)
{
	InitEvents(eventDisp);
}

void view_functionInput::Show()
{
	ImGui::Begin("FunctionInput");
	ImGui::InputTextMultiline("##source", m_funcText, IM_ARRAYSIZE(m_funcText));

	if (ImGui::Button("Run"))
	{
		std::string funcText = m_funcText;
		m_e_SubmitFunction->Fire(funcText);
	}
	ImGui::PushButtonRepeat(true);

	if (ImGui::Button("Right"))
	{
		std::string funcText = m_funcText;
		m_e_RightRot->Fire(true);
	}

	if (ImGui::Button("Left"))
	{
		std::string funcText = m_funcText;
		m_e_LeftRot->Fire(true);
	}
	ImGui::PopButtonRepeat();

	ImGui::End();
}

void view_functionInput::InitEvents(EventDispatcher* eventDisp)
{
	m_e_SubmitFunction = eventDisp->GetEvent<const std::string&>("SubmitFunction");
	m_e_RightRot = eventDisp->GetEvent<bool>("RightRot");
	m_e_LeftRot  = eventDisp->GetEvent<bool>("LeftRot");
}
