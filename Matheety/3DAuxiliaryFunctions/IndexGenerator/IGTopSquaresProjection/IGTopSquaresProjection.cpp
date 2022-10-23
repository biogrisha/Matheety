#include "IGTopSquaresProjection.h"

void IGTopSquaresProjection::GenerateIndices(std::vector<int>& indices, int xCount, int yCount)
{
	int a = 0;
	int b = 1;
	int c = xCount;
	int d = xCount+1;
	indices.resize((xCount-1) * (yCount-1)*6);
	int i = 0;
	for (int y = 0; y < yCount-1; y++)
	{
		for (int x = 0; x < xCount-1; x++)
		{
			indices[0+i]= a;
			indices[1+i]= b;
			indices[2+i]= c;
			indices[3+i]= b;
			indices[4+i]= c;
			indices[5+i]= d;
			i += 6;
			a++;
			b++;
			c++;
			d++;

		}
		a++;
		b++;
		c++;
		d++;
	}
}
