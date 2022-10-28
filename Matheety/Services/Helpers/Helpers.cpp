#include "Helpers.h"
static std::string AppPath = "";
const std::string& Helpers::GetAppPath()

{
	if (AppPath.empty())
	{
		std::string pathTemp;
		WCHAR path[100];
		char Filename[MAX_PATH];
		GetModuleFileNameW(NULL, path, 100);
		std::wstring pathFolder = path;
		auto lastSlashPos = pathFolder.find_last_of('\\');
		pathFolder.erase(pathFolder.end() - (pathFolder.length() - lastSlashPos), pathFolder.end());
		std::string pathFinal(pathFolder.begin(), pathFolder.end());
		AppPath = pathFinal;
	}

	return AppPath;
}

void Helpers::normalizedMouseCoords(double x, double y, double& outX, double& outY, int wWidth, int wHeight)
{
	float mx = x;
	float my = y;
	outX = (mx / ((float)wWidth / 2)) - 1;
	outY = -(my / ((float)wHeight / 2)) + 1;

};

