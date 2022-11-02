#include "ru_coordinateMarks.h"

ru_coordinateMarks::ru_coordinateMarks(GLBP_wrap&& subbuf, uint32_t frameViewId, Camera* camera):RenderUnit(frameViewId)
{
    m_camera = camera;
    m_textRend.reset(new TextRender(std::move(subbuf),&m_glyphLoader));


    m_textRend->AddText("Hello world",0,0,0,2);
    auto t1 = m_textRend->AddText("Hello world 3435",0,1,0,2);
    m_textRend->AddText("Hello world 123",1,0,0,2);
    auto t2 = m_textRend->AddText("Hello world )))",0,0,1,2);
    auto t3 = m_textRend->AddText("Hello world 3",2,0,0,2);

    m_textRend->Update();

}

void ru_coordinateMarks::Update(uint32_t renderTarget)
{
    m_textRend->Render(m_camera,&m_glyphLoader);
}
