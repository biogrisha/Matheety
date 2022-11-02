#include "GraphModule.h"

GraphModule::GraphModule()
{
    //services
   

    m_simpleShader.reset(new Shader("Shaders\\vshad.vs", "Shaders\\fshad.fs"));

    m_camera.SetPosition(0, 0, 10, -90, 0, 0);

    m_glBuf.reset(new GLBuffer(2000, 8000));
    m_frameView =  m_frameViewManager.AddFrameView(std::make_unique<FrameViewBase>(800, 600));
    m_frameView->AddRenderUnit(std::unique_ptr<RenderUnit>(new ru_graph(m_glBuf->NewSubBuffer(1000, 6000), m_frameView->GetId(),&m_camera,&m_graph,m_simpleShader.get())));
    m_frameView->AddRenderUnit(std::unique_ptr<RenderUnit>(new ru_coordinatePlane(m_glBuf->NewSubBuffer(60, 200), m_glBuf->NewSubBuffer(100, 100), m_frameView->GetId(), &m_camera,&m_coordAx,m_simpleShader.get())));
    m_frameView->AddRenderUnit(std::unique_ptr<RenderUnit>(new ru_coordinateMarks(m_glBuf->NewSubBuffer(100, 2), m_frameView->GetId(), &m_camera)));
    
    m_graph.SetPointCount(30);
    m_graph.SetRange(-1, 1, -1, 1);



}

GraphModule::~GraphModule()
{

}

void GraphModule::UpdateGraphFunction(const std::string& body)
{
    m_graph.SetFunction(body);
    m_graph.CalculatePoints();
    m_frameViewManager.RequestUpdate();
    
}

void GraphModule::UpdateState()
{
    m_frameViewManager.ProcessAll(m_glBuf.get());
}

GLuint GraphModule::GetRenderTgt()
{
    return m_frameView->GetRenderTarget();
}

void GraphModule::ChangeCameraDirection(float x, float y)
{
    m_camera.ProcessMouseMovement(x, y);
    m_frameViewManager.RequestUpdate();
}

void GraphModule::MoveCamera(Camera_Movement direction, float deltaTime)
{
    m_camera.ProcessKeyboard(direction, deltaTime);
    m_frameViewManager.RequestUpdate();

}






