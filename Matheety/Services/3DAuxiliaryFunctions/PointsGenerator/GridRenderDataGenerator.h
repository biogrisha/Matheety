#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <Services/GraphicStructs/GraphicStructs.h>
class GridRenderDataGenerator
{
public:
	void GenerateVertices(float strideX, float strideZ, float lengthX, float lenghtZ, const glm::vec4& col);
	const std::vector<Vertex>& GetVertices();
	const std::vector<int>& GetIndices();
private:
	std::vector<Vertex> m_vertices;
	std::vector<int> m_indices;
};
