#pragma once
#include "CoordinateAxis.h"

class CoordinateAxisTraced : public CoordinateAxis
{
public:
	bool IsChanged();
	void Submit();
	void SetDirection(AxisDir dir);
	void SetLength(float length);
	void SetMarkDist(float dist);
private:
	bool m_isChanged = true;
};