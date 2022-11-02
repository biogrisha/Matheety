#include "CoordinateAxisTraced.h"

bool CoordinateAxisTraced::IsChanged()
{
	return m_isChanged;
}

void CoordinateAxisTraced::Submit()
{
	m_isChanged = false;

}

void CoordinateAxisTraced::SetDirection(AxisDir dir)
{
	CoordinateAxis::SetDirection(dir);
	m_isChanged = true;

}

void CoordinateAxisTraced::SetLength(float length)
{
	CoordinateAxis::SetLength(length);
	m_isChanged = true;

}

void CoordinateAxisTraced::SetMarkDist(float dist)
{
	CoordinateAxis::SetMarkDist(dist);
	m_isChanged = true;

}
