#include "VectorFunctions.h"

glm::vec4 VectorFunctions::CrossProduct(const glm::vec4& a, const glm::vec4& b)
{


	return glm::vec4(
		(a.y*b.z)-(a.z*b.y),
		(a.z*b.x)-(a.x*b.z),
		(a.x*b.y)-(a.y*b.x),
		1
	
	);
}

void VectorFunctions::GenerateNormalsPerTriangleGrid(std::vector<glm::vec4>& points, std::vector<glm::vec4>& normals, int xCount, int yCount)
{
	
	std::vector<glm::vec4> normalsPerTriangle;


	int i = 0;
	for (int y = 0; y < yCount - 1; y++)
	{
		for (int x = 0; x < xCount - 1; x++)
		{



			glm::vec4& a = points[i];
			glm::vec4& b = points[i + 1];
			glm::vec4& c = points[i + xCount];
			glm::vec4& d = points[i + xCount + 1];

			glm::vec4 ab = b - a;
			glm::vec4 ac = c - a;
			glm::vec4 db = b - d;
			glm::vec4 dc = c - d;


			normals.push_back(CrossProduct(ac,ab));
			normals.push_back(CrossProduct(db,dc));

			i++;
		}
		i++;
	}
}
