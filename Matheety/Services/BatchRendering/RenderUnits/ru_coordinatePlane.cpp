#include "ru_coordinatePlane.h"

ru_coordinatePlane::ru_coordinatePlane(GLBP_wrap&& axisSubbuf, GLBP_wrap&& gridSubbuf, uint32_t frameViewId, Camera* camera, CoordinateAxisTraced* coordAx, Shader* shader):RenderUnit(frameViewId)
{
	m_axisSubbuf = std::move(axisSubbuf);
	m_gridSubbuf = std::move(gridSubbuf);
	m_camera = camera;
	m_coordAx = coordAx;
	m_shader = shader;
}

void ru_coordinatePlane::Update(uint32_t renderTarget)
{
	if (m_coordAx->IsChanged())
	{
		AxisRenderDataCreator axGenerator;
		axGenerator.SetAxisData(m_coordAx);
		axGenerator.SetThickness(0.007);
		axGenerator.GenerateData();
		GridRenderDataGenerator gridGen;
		glm::vec4 col(0.8, 0.8, 0.8, 0.8);
		gridGen.GenerateVertices(m_coordAx->GetMarkDist(), m_coordAx->GetMarkDist(), m_coordAx->GetLength(), m_coordAx->GetLength(), col);

		m_coordAx->Submit();

		m_axisSubbuf->UpdateIndices(0,axGenerator.GetIndices());
		m_axisSubbuf->UpdateVertices(0, axGenerator.GetVertices());
		m_axisSubbuf->SetIndexCount(axGenerator.GetIndices().size());


		m_gridSubbuf->UpdateIndices(0, gridGen.GetIndices());
		m_gridSubbuf->UpdateVertices(0, gridGen.GetVertices());
		m_gridSubbuf->SetIndexCount(gridGen.GetIndices().size());


	}


	m_shader->use();
	glm::mat4 projection = glm::perspective(glm::radians(m_camera->Zoom), (float)800 / (float)600, 0.5f, 50.0f);
	glm::mat4 view = m_camera->GetViewMatrix();

	m_shader->setMat4("projection", projection);
	m_shader->setMat4("view", view);
	glDrawElements(GL_TRIANGLES, m_axisSubbuf->GetIndexCount(), GL_UNSIGNED_INT, (void*)(m_axisSubbuf->GetIndexOffset() * sizeof(GLuint)));
	glDrawElements(GL_LINES, m_gridSubbuf->GetIndexCount(), GL_UNSIGNED_INT, (void*)(m_gridSubbuf->GetIndexOffset() * sizeof(GLuint)));
	
}
