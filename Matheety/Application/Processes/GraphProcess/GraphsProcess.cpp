#include "GraphsProcess.h"

GraphsProcess::GraphsProcess()
{
	m_graphFuncRel.reset(new ModRel_Graph_FuncInput(&m_graphModule, &m_funcInpView));
	m_graphRendSpace.reset(new ModRel_Graph_RenderSpace(&m_graphModule, &m_rendSpaceView));
}

void GraphsProcess::Run()
{
	m_funcInpView.Show();
	m_rendSpaceView.Show();
	m_graphModule.UpdateState();
}
