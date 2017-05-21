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

	static int GetUpIndexFromArrayIndex(int i_iArrayIndex,int i_iSizeX)
	{
		int UpPosIndex = -1;
		UpPosIndex = i_iArrayIndex - i_iSizeX;
		if (UpPosIndex >= 0)
		{
			return UpPosIndex;
		}
		else
		{
			return -1;
		}		
	};

	static int GetBottomIndexFromArrayIndex(int i_iArrayIndex, int i_iSizeX, int i_iSizeY)
	{
		int BottomPosIndex = -1;
		BottomPosIndex = i_iArrayIndex + i_iSizeX;
		if (BottomPosIndex < i_iSizeY*i_iSizeX)
		{
			return BottomPosIndex;
		}
		else
		{
			return -1;
		}
	};

	static int GetLeftIndexFromArrayIndex(int i_iArrayIndex, int i_iSizeX, int i_iSizeY)
	{
		int LeftIndex = -1;
		LeftIndex = i_iArrayIndex - 1;
		if (LeftIndex >= 0 && i_iArrayIndex % i_iSizeX != 0)
		{
			return LeftIndex;
		}
		else
		{
			return -1;
		}
	};

	static int GetRightIndexFromArrayIndex(int i_iArrayIndex, int i_iSizeX, int i_iSizeY)
	{
		int RightIndex = -1;
		RightIndex = i_iArrayIndex + 1;
		if (RightIndex < i_iSizeY*i_iSizeX && RightIndex % i_iSizeX != 0)
		{
			return RightIndex;
		}
		else
		{
			return -1;
		}
	};
};