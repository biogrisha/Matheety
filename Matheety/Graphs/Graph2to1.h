#pragma once
#include <memory>
#include <iostream>
#include <3DAuxiliaryFunctions/PointsGenerator/PointsGenerator2to1.h>
#include <3DAuxiliaryFunctions/VectorFunctions.h>
#include <3DAuxiliaryFunctions/IndexGenerator/IGTopSquaresProjection/IGTopSquaresProjection.h>

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
	

	struct {
	public:
		void OnPointsUpdated()
		{
			m_pointsChanged = true;
		}
		
		bool IsPointsUpdated()
		{
			return m_pointsChanged;
		}


		void OnCountUpdated()
		{
			m_countChanged = true;
		}

		bool IsCountUpdated()
		{
			return m_countChanged;
		}

		void Submit()
		{
			m_pointsChanged = false;
			m_countChanged = false;

		}
	private:
		bool m_pointsChanged = false;
		bool m_countChanged = false;
	}m_trackChanges;


private:
	std::unique_ptr<DynamicFunctionFabric> m_funcFabric;
	int m_pointsCount = 0;
	float m_xFrom = 0, m_xTo = 0, m_yFrom = 0, m_yTo = 0;
	std::vector<Vertex> m_points;
	std::unique_ptr <DynamicFunction<float,float,float>> m_functionPtr;
	PointsGenerator2to1<DynamicFunction<float, float, float>> m_pointGenerator;

	
};