#pragma once
#include <memory>
#include <iostream>
#include <Services/3DAuxiliaryFunctions/PointsGenerator/PointsGenerator2to1.h>
#include <Services/3DAuxiliaryFunctions/VectorFunctions.h>
#include <Services/3DAuxiliaryFunctions/IndexGenerator/IGTopSquaresProjection/IGTopSquaresProjection.h>
#include <Services/Helpers/Macroses.h>
#include <Services/DynamicFunction/DynamicFunctionFabric.h>
#include <Services/GraphicStructs/GraphicStructs.h>
class Graph2to1
{
public:
	void SetFunction(const std::string& body);
	void SetRange(float xFrom, float xTo,float yFrom, float yTo);
	void GetRange(float& xFrom, float& xTo, float& yFrom, float& yTo);
	void SetPointCount(int count);//Point count in the one direction of square grid
	int GetPointCount();//Point count in the one direction of square grid
	void CalculatePoints();
	std::vector<Vertex>& GetPoints();
	

	struct Events{
	public:
		Getter(IsPointsChanged, pointsChanged, bool)
		Getter(IsCountChanged, countChanged, bool)

		void Submit();

	private:
		bool pointsChanged = false;
		bool countChanged = false;

		friend Graph2to1;
	}events;


private:
	std::unique_ptr<DynamicFunctionFabric> m_funcFabric;
	int m_pointsCount = 0;
	float m_xFrom = 0, m_xTo = 0, m_yFrom = 0, m_yTo = 0;
	std::vector<Vertex> m_points;
	std::unique_ptr<DynamicFunction<float,float,float>> m_functionPtr;
	PointsGenerator2to1<DynamicFunction<float, float, float>> m_pointGenerator;

	
};