#pragma once
#include <vector>
#include <Services/GraphicStructs/GraphicStructs.h>
#include <Services/GraphicStructs/GraphicEnums.h>
class PointsNormalizer2to1
{
public:

	void Normalize(std::vector<Vertex>& points,float range);
};