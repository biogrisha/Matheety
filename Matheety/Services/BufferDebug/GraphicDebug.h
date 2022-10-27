#pragma once

#include <iostream>
#include <vector>
#include "GraphicEnums.h"
#include "GraphicDebugDefinitions.h"
class GraphicDebug
{
public:

	inline static void PrintIndices(const std::vector<int>& inds, EObjectTypes type, std::string desc)
	{
#ifdef GRAPHICS_DEBUG
		/*std::cout << desc << std::endl;
		switch (type)
		{
		case EObjectTypes::Line:
		{
			int sz = inds.size();
			int sz2 = sz - 2;

			for (int i = 0; i < sz; i++)

			{
				std::cout << inds[i] << ", ";
				if (i < sz2 && i>0 && inds[i-1] != inds[i] && inds[i] != inds[i + 1] && inds[i + 1] != inds[i + 2])
				{
					std::cout << std::endl;
				}
			}
			std::cout << std::endl;
			break;
		}
		case EObjectTypes::DashedLine:
			break;
		case EObjectTypes::Area:
			break;
		default:
			break;
		}*/




#endif // GRAPHICS_DEBUG

	}

	inline static void PrintMessage(std::string message)
	{
#ifdef GRAPHICS_DEBUG
		std::cout << message << std::endl;
#endif // GRAPHICS_DEBUG

	}
};