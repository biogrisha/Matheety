#include "ru_coordinateMarks.h"

ru_coordinateMarks::ru_coordinateMarks(GLBP_wrap&& subbuf, uint32_t frameViewId, Camera* camera, CoordinateAxisTraced* coordAx, float* range):RenderUnit(frameViewId)
{
    m_range = range;
    m_camera = camera;
    m_textRend.reset(new TextRender(std::move(subbuf),&m_glyphLoader));
    m_coordAx = coordAx;

    


}

void ru_coordinateMarks::Update(uint32_t renderTarget)
{
    if (*m_range != m_rangeComp)
    {
        m_textRend->Clear();
        for (float x = -m_coordAx->GetLength(); x <= m_coordAx->GetLength(); x += m_coordAx->GetMarkDist() * 2)
        {
            float res = x * ((*m_range) / 2);
            std::string num_text = std::to_string(res);
            std::string rounded;
            if(std::abs(res)<0.1)
                rounded = num_text.substr(0, num_text.find(".") + 3);
            else
                rounded = num_text.substr(0, num_text.find(".") + 2);

            m_textRend->AddText(rounded, x, 0, 0, 1);
            m_textRend->AddText(rounded, 0, 0, x, 1);

        }
        m_textRend->Update();

        m_rangeComp = *m_range;
    }
    m_textRend->Render(m_camera,&m_glyphLoader);
}
