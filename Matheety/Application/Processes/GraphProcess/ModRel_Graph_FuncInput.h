#pragma once
#include <Modules/GraphModule.h>
#include <Views/FunctionInput/view_functionInput.h>

class ModRel_Graph_FuncInput
{
public:
	ModRel_Graph_FuncInput(GraphModule* mod, view_functionInput* view)
	{
		m_mod = mod;
		m_view = view;
		
		e_onRunClicked.reset(view->events.btn_click_run.AddHandler(&ModRel_Graph_FuncInput::RunClickedProc, this));
		e_onViewDispose.reset(view->events.dispose.AddHandler(&ModRel_Graph_FuncInput::ViewDisposeProc, this));
		e_onRangeSet.reset(view->events.rangeChanged.AddHandler(&ModRel_Graph_FuncInput::RangeChanged, this));
	}

	void RunClickedProc(const std::string& body)
	{
		m_mod->UpdateGraphFunction(body);
	}

	void  ViewDisposeProc(bool)
	{
		e_onRunClicked.reset();
		e_onViewDispose.reset();
		e_onRangeSet.reset();
	}

	void RangeChanged(float val)
	{
		m_mod->SetGraphRange(val);
	}
private:
	EventHandlerRAII<const std::string&> e_onRunClicked;
	EventHandlerRAII<bool> e_onViewDispose;
	EventHandlerRAII<float> e_onRangeSet;

	GraphModule* m_mod;
	view_functionInput* m_view;
};
