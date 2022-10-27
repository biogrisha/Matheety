#pragma once
#include <Modules/GraphModule.h>
#include "ModRel_Graph_FuncInput.h"
#include "ModRel_Graph_RenderSpace.h"
class GraphsProcess
{
public:
	GraphsProcess();
	void Run();

private:
	GraphModule m_graphModule;
	view_functionInput m_funcInpView;
	view_renderSpace m_rendSpaceView;
	std::unique_ptr<ModRel_Graph_FuncInput> m_graphFuncRel;
	std::unique_ptr<ModRel_Graph_RenderSpace> m_graphRendSpace;
};