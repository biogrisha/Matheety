#pragma once
#include "Processes/GraphProcess/GraphsProcess.h"
class Application
{
public:
	Application();
	void Run();

private:
	GraphsProcess m_graphProc;

};