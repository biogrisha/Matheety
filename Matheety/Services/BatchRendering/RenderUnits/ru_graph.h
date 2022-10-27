#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Services/3DAuxiliaryFunctions/Camera.h>
#include <Services/3DAuxiliaryFunctions/IndexGenerator/IGTopSquaresProjection/IGTopSquaresProjection.h>
#include <Services/Graphs/Graph2to1.h>
#include <Services/Shader/shader_s.h>
#include "../RenderUnit.h"
#include "../GLBuffer.h"

class ru_graph : public RenderUnit
{
public:
	ru_graph(GLBP_wrap&& subbuf, uint32_t frameViewId, Camera* camera, glm::mat4* graphTransform, Graph2to1* graph);
	// Inherited via RenderUnit
	virtual void Update(uint32_t renderTarget) override;

private:

	GLBP_wrap m_subbuf;
	Camera* m_camera;
	Graph2to1* m_graph;
	glm::mat4* m_graphTransform;
	std::unique_ptr<Shader> m_shader;
};