#pragma once
#include <Services/GraphicStructs/GraphicStructs.h>
#include <vector>
#include <Services/Helpers/Macroses.h>
enum class AxisDir
{
	X,Y,Z
};

class CoordinateAxis
{
public:
	void SetDirection(AxisDir dir);
	void SetLength(float length);
	void SetMarkDist(float dist);

	Getter(Direction, m_axisDir, AxisDir)
	Getter(Length, m_length, float)
	Getter(MarkDist, m_markDist, float)
protected:
	AxisDir m_axisDir = AxisDir::X;
	float m_length = 2;
	float m_markDist = 0.5;

};