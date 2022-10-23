#pragma once
#include <memory>
#include <BatchRendering\FrameViewManager.h>
#include <BatchRendering\GLBuffer.h>
#include <BatchRendering/RenderUnits/ru_graph.h>
#include <Graphs/Graph2to1.h>
#include <Views/FunctionInput/view_functionInput.h>
#include <Application/Events.h>

class GraphRenderProcess
{
public:
	GraphRenderProcess();
	~GraphRenderProcess();
	void UpdateState();
	GLuint GetRenderTarget();

private:
	
	std::unique_ptr <GLBuffer> m_glBuf;
	FrameViewManager m_frameViewManager;
	FrameViewBase* m_frameView;
	Graph2to1 m_graph;
	Camera m_camera;
	glm::mat4 m_graphTransform;
	std::unique_ptr <view_functionInput> m_funcInput;



	//Events
	void InitEvents();

	EventDispatcher m_eventDisp;
	Event<const std::string&>* m_e_SubmitFunction = nullptr;
	Event<bool>* m_e_RightRot = nullptr;
	Event<bool>* m_e_LeftRot = nullptr;
	Event<bool>* m_e_UpRot = nullptr;
	Event<bool>* m_e_DownRot = nullptr;

public:
	void Proc_SubmitFunction(const std::string& funcText);
	void Proc_RightRot();
	void Proc_LeftRot();
	void Proc_UpRot();
	void Proc_DownRot();

	
};
