#include "CoordinateAxis.h"

void CoordinateAxis::SetDirection(AxisDir dir)
{
	m_axisDir = dir;
}

void CoordinateAxis::SetLength(float length)
{
	m_length = length;
}

void CoordinateAxis::SetMarkDist(float dist)
{
	m_markDist = dist;
}
