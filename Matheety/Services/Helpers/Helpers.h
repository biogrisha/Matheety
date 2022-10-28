#pragma once

#include <Windows.h>
#include <iostream>
#include <string>

namespace Helpers
{
	//System related
    template<typename Str, typename memType>
    void ResetUniformStruct(Str* strPtr)
    {

        int sz = sizeof(*strPtr) / sizeof(memType);
        if (sz > 1)
        {

            bool* ptr = reinterpret_cast<memType*>(strPtr);
            for (int i = 0; i < sz; i++)
            {
                *(ptr + i) = 0;
            }
        }
    }

	const std::string& GetAppPath();

    void normalizedMouseCoords(double x, double y, double& outX, double& outY, int wWidth, int wHeight);
}