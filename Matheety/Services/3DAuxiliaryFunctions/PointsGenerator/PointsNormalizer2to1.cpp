#include "PointsNormalizer2to1.h"

void PointsNormalizer2to1::Normalize(std::vector<Vertex>& points, float range)
{
	float halfRange = range / 2.0f;

	for (auto& point : points)
	{

		point.pos.x /= halfRange;
		point.pos.z /= halfRange;
		point.pos.y /= halfRange;

	}
}
