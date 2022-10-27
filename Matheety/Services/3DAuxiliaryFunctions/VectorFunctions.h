#pragma once
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace VectorFunctions
{
	glm::vec4 CrossProduct(const glm::vec4& a, const glm::vec4& b);

	void GenerateNormalsPerTriangleGrid(std::vector<glm::vec4>& points, std::vector<glm::vec4>& normals, int xCount, int yCount);
}