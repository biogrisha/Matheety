#pragma once
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Services/3DAuxiliaryFunctions/Camera.h>
#include <Services/3DAuxiliaryFunctions/IndexGenerator/IGTopSquaresProjection/IGTopSquaresProjection.h>
#include <Services/Graphs/Graph2to1.h>
#include <Services/Shader/shader_s.h>
#include <Services/CoordinateAxis/CoordinateAxisTraced.h>
#include <Services/CoordinateAxis/AxisRenderDataCreator.h>
#include <Services/3DAuxiliaryFunctions/PointsGenerator/GridRenderDataGenerator.h>
#include "../RenderUnit.h"
#include "../GLBuffer.h"

class ru_coordinatePlane : public RenderUnit
{
public:
	ru_coordinatePlane(GLBP_wrap&& axisSubbuf, GLBP_wrap&& gridSubbuf, uint32_t frameViewId, Camera* camera, CoordinateAxisTraced* coordAx, Shader* shader);
	// Inherited via RenderUnit
	virtual void Update(uint32_t renderTarget) override;

private:
	Shader* m_shader;
	GLBP_wrap m_axisSubbuf;
	GLBP_wrap m_gridSubbuf;
	Camera* m_camera;
	CoordinateAxisTraced* m_coordAx;
	std::vector<Vertex> m_vertices;
	std::vector<int> m_indices;

};