#include "GridRenderDataGenerator.h"

void GridRenderDataGenerator::GenerateVertices(float strideX, float strideZ, float lengthX, float lengthZ, const glm::vec4& col)
{
	m_vertices.clear();
	m_indices.clear();
	int xCount = (lengthZ / strideX);
	int zCount = (lengthX / strideZ);

	glm::vec4 x1(lengthX, 0, 0,0);
	glm::vec4 x2(-lengthX, 0, 0,0);
	glm::vec4 xTrans(0, 0, strideX, 0);

	glm::vec4 z1( 0, 0, lengthZ, 0);
	glm::vec4 z2( 0, 0, -lengthZ, 0);
	glm::vec4 zTrans(strideZ, 0, 0, 0);

	for (int x = 0; x < xCount; x++)
	{

		m_vertices.push_back({ x1,col });
		m_vertices.push_back({ x2,col });
		x1+= xTrans;
		x2+= xTrans;

	}

	x1 = glm::vec4(lengthX, 0, 0, 0);
	x2 = glm::vec4(-lengthX, 0, 0, 0);
	for (int x = 1; x < xCount; x++)
	{
		x1 -= xTrans;
		x2 -= xTrans;

		m_vertices.push_back({ x1,col });
		m_vertices.push_back({ x2,col });

	}


	for (int z = 0; z < zCount; z++)
	{

		m_vertices.push_back({ z1,col });
		m_vertices.push_back({ z2,col });
		z1 += zTrans;
		z2 += zTrans;

	}

	z1 = glm::vec4(0, 0, lengthZ, 0);
	z2 = glm::vec4(0, 0, -lengthZ, 0);
	for (int z = 1; z < zCount; z++)
	{
		z1 -= zTrans;
		z2 -= zTrans;

		m_vertices.push_back({ z1,col });
		m_vertices.push_back({ z2,col });

	}

	for (int i = 0; i < m_vertices.size(); i++)
	{
		m_indices.push_back(i);
	}
}

const std::vector<Vertex>& GridRenderDataGenerator::GetVertices()
{
	return m_vertices;
}

const std::vector<int>& GridRenderDataGenerator::GetIndices()
{
	return m_indices;
}

