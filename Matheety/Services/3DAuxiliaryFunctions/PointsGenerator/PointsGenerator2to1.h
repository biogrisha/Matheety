#pragma once
#include <memory>
#include <math.h>
#include <exception>
#include <Services/DynamicFunction/DynamicFunctionFabric.h>
#include <Services/GraphicStructs/GraphicStructs.h>
#include <Services/Helpers/trait_is_right_callable.h>

template<typename Functor>
class PointsGenerator2to1
{
public:
	static_assert(is_right_callable<Functor, float,float,float>::value, "Functor must be callable and has following signature 'float funcName(float,float)'");
	void SetFunction(Functor* funcPtr)
	{
		m_funcPtr = funcPtr;
	}

	void CalculatePoints(std::vector<Vertex>& res, float x1, float x2, float y1, float y2, int pointsCount);
	

private:
	DynamicFunction<float, float, float>* m_funcPtr = nullptr;
};

template<typename Functor>
inline void PointsGenerator2to1<Functor>::CalculatePoints(std::vector<Vertex>& res, float x1, float x2, float y1, float y2, int pointsCount)
{
	if (!m_funcPtr)
	{
		throw std::exception("You must provide the function pointer before calculating");
	}
	bool x1Smaller = x1 < x2;
	bool y1Smaller = y1 < y2;

	if (!x1Smaller)
	{
		std::swap(x1, x2);
	}
	if (!y1Smaller)
	{
		std::swap(y1, y2);
	}

	float xDist = x2 - x1;
	float yDist = y2 - y1;
	float xStep = xDist / (pointsCount - 1);
	float yStep = yDist / (pointsCount - 1);

	float x = x1;
	for (int i = 0; i < pointsCount; i++)
	{
		float y = y1;
		for (int j = 0; j < pointsCount; j++)
		{
			float z = (*m_funcPtr)(x, y);
			res.push_back({ glm::vec4(x,y,z,1),glm::vec4()});
			y += yStep;
		}
		x += xStep;
	}
}
