#pragma once
#include <Services/Shader/shader_s.h>
#include <Services/TextRendering/TextRender.h>
#include <Services/3DAuxiliaryFunctions/Camera.h>
#include <Services/CoordinateAxis/CoordinateAxisTraced.h>
#include "../RenderUnit.h"
#include "../GLBuffer.h"

class ru_coordinateMarks : public RenderUnit
{
public:
	ru_coordinateMarks(GLBP_wrap&& subbuf, uint32_t frameViewId, Camera* camera, CoordinateAxisTraced* coordAx,float* range);
	virtual void Update(uint32_t renderTarget) override;

private:
	GlyphLoader m_glyphLoader;
	std::unique_ptr<TextRender> m_textRend;
	Camera* m_camera;
	CoordinateAxisTraced* m_coordAx;
	float* m_range = NULL;
	float m_rangeComp = 1;
};