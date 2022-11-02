#include "ru_graph.h"

ru_graph::ru_graph(GLBP_wrap&& subbuf, uint32_t frameViewId, Camera* camera, Graph2to1* graph, Shader* shader):RenderUnit(frameViewId)
{
	m_subbuf = std::move(subbuf);
	m_camera = camera;
	m_graph = graph;
	m_shader = shader;
}

void ru_graph::Update(uint32_t renderTarget)
{

	if (m_graph->events.GetIsCountChanged())
	{
		std::vector<int> inds;
		IGTopSquaresProjection::GenerateIndices(inds, m_graph->GetPointCount(), m_graph->GetPointCount());
		m_subbuf->UpdateIndices(0, inds);
		m_subbuf->SetIndexCount(inds.size());
	}

	if (m_graph->events.GetIsPointsChanged())
	{
		m_subbuf->UpdateVertices(0, m_graph->GetPoints());
	}
	m_graph->events.Submit();

	m_shader->use();
	glm::mat4 projection = glm::perspective(glm::radians(m_camera->Zoom), (float)800 / (float)600, 0.5f, 50.0f);
	glm::mat4 view = m_camera->GetViewMatrix();

	m_shader->setMat4("projection", projection);
	m_shader->setMat4("view", view);
	glDrawElements(GL_TRIANGLES, m_subbuf->GetIndexCount(), GL_UNSIGNED_INT, (void*)(m_subbuf->GetIndexOffset() * sizeof(GLuint)));

}
