#pragma once
#include <Services/CoordinateAxis/CoordinateAxis.h>

class AxisRenderDataCreator
{
public:
	AxisRenderDataCreator();
	void SetAxisData(CoordinateAxis* data);
	void SetThickness(float val);
	void GenerateData();
	const std::vector<Vertex>& GetVertices();
	const std::vector<int>& GetIndices();
private:
	void GenerateAxisBar(AxisDir dir);

	CoordinateAxis* m_data = nullptr;
	float m_thickness = 0.1;
	glm::vec4 m_color;

	std::vector<Vertex> m_verts;
	std::vector<int> m_inds;

	//technical
	int m_lastVecUpdated = 0;
};