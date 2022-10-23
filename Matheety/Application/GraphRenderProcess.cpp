#include "GraphRenderProcess.h"

GraphRenderProcess::GraphRenderProcess()
{
    
    InitEvents();
    m_funcInput.reset(new view_functionInput(&m_eventDisp));


    m_glBuf.reset(new GLBuffer(1000, 6000));
    m_frameView =  m_frameViewManager.AddFrameView(std::make_unique<FrameViewBase>(800, 600));
    m_frameView->AddRenderUnit(std::unique_ptr<RenderUnit>(new ru_graph(m_glBuf->NewSubBuffer(1000, 6000), m_frameView->GetId(),&m_camera,&m_graphTransform,&m_graph)));
    
    m_graph.SetPointCount(30);
    m_graph.SetRange(-1, 1, -1, 1);
}

GraphRenderProcess::~GraphRenderProcess()
{

}

void GraphRenderProcess::UpdateState()
{
    m_frameViewManager.RequestUpdate();

    m_frameViewManager.ProcessAll(m_glBuf.get());
    m_funcInput->Show();
}

GLuint GraphRenderProcess::GetRenderTarget()
{
    return m_frameView->GetRenderTarget();
}

void GraphRenderProcess::InitEvents()
{
    m_e_SubmitFunction = m_eventDisp.AddEvent<const std::string&>(
        [](const std::string& tgt, void* obj) {static_cast<GraphRenderProcess*>(obj)->Proc_SubmitFunction(tgt); }, "SubmitFunction", this);
    m_e_RightRot = m_eventDisp.AddEvent<bool>(
        [](bool,void* obj) {static_cast<GraphRenderProcess*>(obj)->Proc_RightRot(); }, "RightRot", this);
    m_e_LeftRot = m_eventDisp.AddEvent<bool>(
        [](bool, void* obj) {static_cast<GraphRenderProcess*>(obj)->Proc_LeftRot(); }, "LeftRot", this);
    m_e_UpRot = m_eventDisp.AddEvent<bool>(
        [](bool, void* obj) {static_cast<GraphRenderProcess*>(obj)->Proc_LeftRot(); }, "LeftRot", this);
    m_e_DownRot = m_eventDisp.AddEvent<bool>(
        [](bool, void* obj) {static_cast<GraphRenderProcess*>(obj)->Proc_LeftRot(); }, "LeftRot", this);

}

void GraphRenderProcess::Proc_SubmitFunction(const std::string& funcText)
{

    m_graph.SetFunction(funcText);
    m_graph.CalculatePoints();
}

void GraphRenderProcess::Proc_RightRot()
{
    m_graphTransform = glm::rotate(m_graphTransform, glm::radians(5.0f), glm::vec3(0.0, 1.0, 0.0));
    
}

void GraphRenderProcess::Proc_LeftRot()
{
    m_graphTransform = glm::rotate(m_graphTransform, glm::radians(-5.0f), glm::vec3(0.0, 1.0, 0.0));

    
}

