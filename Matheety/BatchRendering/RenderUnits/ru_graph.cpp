#include "ru_graph.h"

ru_graph::ru_graph(GLBP_wrap&& subbuf, uint32_t frameViewId, Camera* camera, glm::mat4* graphTransform, Graph2to1* graph):RenderUnit(frameViewId)
{
	m_subbuf = std::move(subbuf);
	m_camera = camera;
	m_graphTransform = graphTransform;
	m_graph = graph;
	m_shader.reset(new Shader("Shaders\\vshad.vs", "Shaders\\fshad.fs"));
}

void ru_graph::Update(uint32_t renderTarget)
{
	static float zDist = 10;
	static bool zDir = false;

	if (zDist > 10)
	{
		zDir = true;
	}
	if (zDist < 5)
	{
		zDir = false;
	}

	zDist += 0.03 * (-1 * zDir + 1 * (!zDir));

	if (m_graph->m_trackChanges.IsCountUpdated())
	{
		std::vector<int> inds;
		IGTopSquaresProjection::GenerateIndices(inds, m_graph->GetPointCount(), m_graph->GetPointCount());
		m_subbuf->UpdateIndices(0, inds);
		m_subbuf->SetIndexCount(inds.size());
	}

	if (m_graph->m_trackChanges.IsPointsUpdated())
	{
		m_subbuf->UpdateVertices(0, m_graph->GetPoints());
	}

	m_camera->SetPosition(0, 0, zDist, -90, 0, 0);

	m_shader->use();
	glm::mat4 projection = glm::perspective(glm::radians(m_camera->Zoom), (float)800 / (float)600, 0.5f, 50.0f);
	glm::mat4 view = m_camera->GetViewMatrix();

	m_shader->setMat4("projection", projection);
	m_shader->setMat4("model", *m_graphTransform);
	m_shader->setMat4("view", view);
	glDrawElements(GL_TRIANGLES, m_subbuf->GetIndexCount(), GL_UNSIGNED_INT, (void*)(m_subbuf->GetIndexOffset() * sizeof(GLuint)));

}
