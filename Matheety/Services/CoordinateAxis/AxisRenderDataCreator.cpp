#include "AxisRenderDataCreator.h"

AxisRenderDataCreator::AxisRenderDataCreator()
{
	m_color = glm::vec4(0.8, 0.8, 0.8, 1);
}

void AxisRenderDataCreator::SetAxisData(CoordinateAxis* data)
{
	m_data = data;
}

void AxisRenderDataCreator::SetThickness(float val)
{
	m_thickness = val;
}

void AxisRenderDataCreator::GenerateData()
{
	m_verts.clear();
	m_verts.resize(54);

	m_lastVecUpdated = 0;
	GenerateAxisBar(AxisDir::X);
	GenerateAxisBar(AxisDir::Y);
	GenerateAxisBar(AxisDir::Z);
}

const std::vector<Vertex>& AxisRenderDataCreator::GetVertices()
{
	return m_verts;
}

const std::vector<int>& AxisRenderDataCreator::GetIndices()
{
	return m_inds;
}

void AxisRenderDataCreator::GenerateAxisBar(AxisDir dir)
{
	glm::mat4 trans;

	switch (dir)
	{
	case AxisDir::Y:
		trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
		break;
	case AxisDir::Z:
		trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
		break;
	default:
		break;
	}

	int countFrom = m_lastVecUpdated;
	std::vector<int> temp =
	{
		0+m_lastVecUpdated,5+m_lastVecUpdated,4+m_lastVecUpdated,
		0+m_lastVecUpdated,5+m_lastVecUpdated,1+m_lastVecUpdated,
		1+m_lastVecUpdated,6+m_lastVecUpdated,5+m_lastVecUpdated,
		1+m_lastVecUpdated,6+m_lastVecUpdated,2+m_lastVecUpdated,
		2+m_lastVecUpdated,7+m_lastVecUpdated,6+m_lastVecUpdated,
		2+m_lastVecUpdated,7+m_lastVecUpdated,3+m_lastVecUpdated,
		3+m_lastVecUpdated,4+m_lastVecUpdated,7+m_lastVecUpdated,
		3+m_lastVecUpdated,4+m_lastVecUpdated,0+m_lastVecUpdated,

		0+8+m_lastVecUpdated,1+8+m_lastVecUpdated,2+8+m_lastVecUpdated,
		0+8+m_lastVecUpdated,2+8+m_lastVecUpdated,3+8+m_lastVecUpdated,
		0+8+m_lastVecUpdated,1+8+m_lastVecUpdated,4+8+m_lastVecUpdated,
		1+8+m_lastVecUpdated,2+8+m_lastVecUpdated,4+8+m_lastVecUpdated,
		2+8+m_lastVecUpdated,3+8+m_lastVecUpdated,4+8+m_lastVecUpdated,
		3+8+m_lastVecUpdated,0+8+m_lastVecUpdated,4+8+m_lastVecUpdated,

		0+13+m_lastVecUpdated,1+13+m_lastVecUpdated,2+13+m_lastVecUpdated,
		0+13+m_lastVecUpdated,2+13+m_lastVecUpdated,3+13+m_lastVecUpdated,
		0+13+m_lastVecUpdated,1+13+m_lastVecUpdated,4+13+m_lastVecUpdated,
		1+13+m_lastVecUpdated,2+13+m_lastVecUpdated,4+13+m_lastVecUpdated,
		2+13+m_lastVecUpdated,3+13+m_lastVecUpdated,4+13+m_lastVecUpdated,
		3+13+m_lastVecUpdated,0+13+m_lastVecUpdated,4+13+m_lastVecUpdated,
	};
	m_inds.insert(m_inds.end(), temp.begin(), temp.end());



	m_verts[m_lastVecUpdated++] = { glm::vec4(m_data->GetLength(),-m_thickness / 2,-m_thickness / 2,0),m_color };
	m_verts[m_lastVecUpdated++] = { glm::vec4(m_data->GetLength(),m_thickness / 2,-m_thickness / 2,0),m_color };
	m_verts[m_lastVecUpdated++] = { glm::vec4(m_data->GetLength(),m_thickness / 2,m_thickness / 2,0),m_color };
	m_verts[m_lastVecUpdated++] = { glm::vec4(m_data->GetLength(),-m_thickness / 2,m_thickness / 2,0),m_color };

	m_verts[m_lastVecUpdated++] = { glm::vec4(-m_data->GetLength(),-m_thickness / 2,-m_thickness / 2,0),m_color };
	m_verts[m_lastVecUpdated++] = { glm::vec4(-m_data->GetLength(),m_thickness / 2,-m_thickness / 2,0),m_color };
	m_verts[m_lastVecUpdated++] = { glm::vec4(-m_data->GetLength(),m_thickness / 2,m_thickness / 2,0),m_color };
	m_verts[m_lastVecUpdated++] = { glm::vec4(-m_data->GetLength(),-m_thickness / 2,m_thickness / 2,0),m_color };

	//arrow
	float arrowSize = m_thickness * 3;
	float arrowLength = arrowSize * 8;
	m_verts[m_lastVecUpdated++] = { glm::vec4(m_data->GetLength(),-arrowSize,-arrowSize,0),m_color };
	m_verts[m_lastVecUpdated++] = { glm::vec4(m_data->GetLength(),arrowSize,-arrowSize,0),m_color };
	m_verts[m_lastVecUpdated++] = { glm::vec4(m_data->GetLength(),arrowSize,arrowSize,0),m_color };
	m_verts[m_lastVecUpdated++] = { glm::vec4(m_data->GetLength(),-arrowSize,arrowSize,0),m_color };

	m_verts[m_lastVecUpdated++] = { glm::vec4(m_data->GetLength() + arrowLength ,0,0,0),m_color };

	m_verts[m_lastVecUpdated++] = { glm::vec4(-m_data->GetLength(),-arrowSize,-arrowSize,0),m_color };
	m_verts[m_lastVecUpdated++] = { glm::vec4(-m_data->GetLength(),arrowSize,-arrowSize,0),m_color };
	m_verts[m_lastVecUpdated++] = { glm::vec4(-m_data->GetLength(),arrowSize,arrowSize,0),m_color };
	m_verts[m_lastVecUpdated++] = { glm::vec4(-m_data->GetLength(),-arrowSize,arrowSize,0),m_color };

	m_verts[m_lastVecUpdated++] = { glm::vec4(-m_data->GetLength() - arrowLength,0,0,0),m_color };

	if (dir != AxisDir::X)
	{
		for (int i = countFrom; i < m_lastVecUpdated; i++)
		{
			m_verts[i].pos =  trans* m_verts[i].pos;
		}

	}

}


