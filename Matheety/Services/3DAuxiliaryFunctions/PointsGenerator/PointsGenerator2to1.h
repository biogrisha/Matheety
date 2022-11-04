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

	void CalculatePoints(std::vector<Vertex>& res, float x1, float x2, float z1, float z2, int pointsCount);
	

private:
	DynamicFunction<float, float, float>* m_funcPtr = nullptr;
};

template<typename Functor>
inline void PointsGenerator2to1<Functor>::CalculatePoints(std::vector<Vertex>& res, float x1, float x2, float z1, float z2, int pointsCount)
{
	if (!m_funcPtr)
	{
		throw std::exception("You must provide the function pointer before calculating");
	}
	bool x1Smaller = x1 < x2;
	bool z1Smaller = z1 < z2;

	if (!x1Smaller)
	{
		std::swap(x1, x2);
	}
	if (!z1Smaller)
	{
		std::swap(z1, z2);
	}

	float xDist = x2 - x1;
	float zDist = z2 - z1;
	float xStep = xDist / (pointsCount - 1);
	float zStep = zDist / (pointsCount - 1);

	float x = x1;
	for (int i = 0; i < pointsCount; i++)
	{
		float z = z1;
		for (int j = 0; j < pointsCount; j++)
		{
			float y = (*m_funcPtr)(x, z);
			res.push_back({ glm::vec4(x,y,z,1),glm::vec4(0.5,z/5+0.5,0.5,1)});
			z += zStep;
		}
		x += xStep;
	}

}
