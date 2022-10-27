#include "Graph2to1.h"

void Graph2to1::SetFunction(const std::string& body)
{
    m_funcFabric.reset();
    FF_DllFolderManager::ClearMainFolder();//ga

    m_funcFabric.reset(new DynamicFunctionFabric);
    m_funcFabric->AddFunction("float Calc(float x, float y)", body);
    m_funcFabric->Build();
    m_functionPtr.reset(new DynamicFunction<float,float,float>(m_funcFabric->LoadFunction<float, float, float>("Calc")));
    m_pointGenerator.SetFunction(m_functionPtr.get());

}

void Graph2to1::SetRange(float xFrom, float xTo, float yFrom, float yTo)
{
    m_xFrom = xFrom;
    m_xTo   = xTo  ;
    m_yFrom = yFrom;
    m_yTo   = yTo  ;

}

void Graph2to1::GetRange(float& xFrom, float& xTo, float& yFrom, float& yTo)
{
    xFrom = m_xFrom;
    xTo = m_xTo;
    yFrom = m_yFrom;
    yTo = m_yTo;
}

void Graph2to1::SetPointCount(int count)
{
    if (m_pointsCount != count)
    {
        events.countChanged = true;
    }
    m_pointsCount = count;

}

int Graph2to1::GetPointCount()
{
    return m_pointsCount;
}

void Graph2to1::CalculatePoints()
{
    events.pointsChanged = true;
    m_points.clear();
    m_pointGenerator.CalculatePoints(m_points, m_xFrom, m_xTo, m_yFrom, m_yTo,m_pointsCount);
}

std::vector<Vertex>& Graph2to1::GetPoints()
{
    return m_points;
}

void Graph2to1::Events::Submit()
{
    pointsChanged = false;
    countChanged = false;

}
