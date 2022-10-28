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
		onMouseDrag.reset(m_view->events.onMouseDrag.AddHandler(&ModRel_Graph_RenderSpace::onMouseDragProc, this));
		onForward.reset(m_view->events.onWKey.AddHandler(&ModRel_Graph_RenderSpace::onForwardProc, this));
		onBack.reset(m_view->events.onSKey.AddHandler(&ModRel_Graph_RenderSpace::onBackProc, this));
		onRight.reset(m_view->events.onDKey.AddHandler(&ModRel_Graph_RenderSpace::onRightProc, this));
		onLeft.reset(m_view->events.onAKey.AddHandler(&ModRel_Graph_RenderSpace::onLeftProc, this));
	}

	void onMouseDragProc(float x, float y)
	{
		m_mod->ChangeCameraDirection(x, y);
	}

	void onForwardProc(float deltaTime)
	{
		m_mod->MoveCamera(Camera_Movement::FORWARD, deltaTime);
	}
	void onBackProc(float deltaTime)
	{
		m_mod->MoveCamera(Camera_Movement::BACKWARD, deltaTime);
	}
	void onRightProc(float deltaTime)
	{
		m_mod->MoveCamera(Camera_Movement::RIGHT, deltaTime);
	}
	void onLeftProc(float deltaTime)
	{
		m_mod->MoveCamera(Camera_Movement::LEFT, deltaTime);
	}
	
private:

	EventHandlerRAII<float, float> onMouseDrag;
	EventHandlerRAII<float> onForward;
	EventHandlerRAII<float> onBack;
	EventHandlerRAII<float> onRight;
	EventHandlerRAII<float> onLeft;

	GraphModule* m_mod;
	view_renderSpace* m_view;
};