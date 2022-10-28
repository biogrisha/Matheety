#pragma once
#include <memory>
#include <Services\BatchRendering\FrameViewManager.h>
#include <Services\BatchRendering\GLBuffer.h>
#include <Services\BatchRendering/RenderUnits/ru_graph.h>
#include <Services\Graphs/Graph2to1.h>
#include <Services/3DAuxiliaryFunctions/Camera.h>

class GraphModule
{
public:
	GraphModule();
	~GraphModule();
	void UpdateGraphFunction(const std::string& body);
	void UpdateState();
	GLuint GetRenderTgt();
	void ChangeCameraDirection(float x, float y);
	void MoveCamera(Camera_Movement direction, float deltaTime);
private:
	
	std::unique_ptr <GLBuffer> m_glBuf;
	FrameViewManager m_frameViewManager;
	FrameViewBase* m_frameView;
	Camera m_camera;
	Graph2to1 m_graph;
	glm::mat4 m_graphTransform;

};
