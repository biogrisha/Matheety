#pragma once

#include <Modules/GraphModule.h>
#include <Views/RenderSpace/view_renderSpace.h>

class ModRel_Graph_RenderSpace
{
public:
	ModRel_Graph_RenderSpace(GraphModule* mod, view_renderSpace* view)
	{
		m_mod = mod;
		m_view = view;
		m_view->SetRenderTarget(m_mod->GetRenderTgt());
	}

	
private:

	GraphModule* m_mod;
	view_renderSpace* m_view;
};