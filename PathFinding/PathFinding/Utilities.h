#pragma once

namespace Utilities
{
	static void GetGridIndexFromArrayIndex(int i_iArrayIndex, int* o_iXCoord, int* o_iYCoord, int i_iSizeX, int i_iSizeY)
	{
		*o_iYCoord = 0;
		*o_iYCoord = (int)(i_iArrayIndex / i_iSizeY);
		*o_iXCoord = 0;
		*o_iXCoord = (int)(i_iArrayIndex % i_iSizeX);
		/*using namespace std;
		cout << "From ArrayIndex: "<< i_iArrayIndex << " --> (x,y):(" << *o_iXCoord << "," << *o_iYCoord << ")" << endl;*/
	};

	static void GetArrayIndexFromGridIndex(int* o_iArrayIndex, int i_iXCoord, int i_iYCoord, int i_iSizeX, int i_iSizeY)
	{
		*o_iArrayIndex = 0;
		*o_iArrayIndex += i_iYCoord * i_iSizeY;
		*o_iArrayIndex += i_iXCoord % i_iSizeY;
		/*using namespace std;
		cout << "From GridIndex: (x,y):(" << i_iXCoord << "," << i_iYCoord << ") --> ArrayIndex: " << *o_iArrayIndex <<  endl;*/
	};
};