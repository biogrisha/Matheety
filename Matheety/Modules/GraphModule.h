#pragma once
#include <memory>
#include <Services\BatchRendering\FrameViewManager.h>
#include <Services\BatchRendering\GLBuffer.h>
#include <Services\BatchRendering/RenderUnits/ru_graph.h>
#include <Services\Graphs/Graph2to1.h>
#include <Services/3DAuxiliaryFunctions/Camera.h>
#include <Services/CoordinateAxis/CoordinateAxisTraced.h>
#include <Services/BatchRendering/RenderUnits/ru_coordinatePlane.h>
#include <Services/BatchRendering/RenderUnits/ru_coordinateMarks.h>
#include <Services/TextRendering/TextRender.h>
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
	void SetGraphRange(float val);
private:
	
	std::unique_ptr <GLBuffer> m_glBuf;
	std::unique_ptr<Shader> m_simpleShader;
	FrameViewManager m_frameViewManager;
	FrameViewBase* m_frameView;
	Camera m_camera;
	Graph2to1 m_graph;
	CoordinateAxisTraced m_coordAx;
	float m_range = 1;
	GLuint m_depthTexture;
	
};
