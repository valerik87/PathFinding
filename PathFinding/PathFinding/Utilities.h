#pragma once
#include "Logger.h"

namespace Utilities
{
	static void GetGridIndexFromArrayIndex(int i_iArrayIndex, int* o_iXCoord, int* o_iYCoord, int i_iSizeX, int i_iSizeY)
	{
		*o_iYCoord = 0;
		*o_iYCoord = (int)(i_iArrayIndex / i_iSizeY);
		*o_iXCoord = 0;
		*o_iXCoord = (int)(i_iArrayIndex % i_iSizeX);
		Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::UTILITIES, "From ArrayIndex: %i to (%i,%i)", i_iArrayIndex,*o_iXCoord,*o_iYCoord);
	};

	static void GetArrayIndexFromGridIndex(int* o_iArrayIndex, int i_iXCoord, int i_iYCoord, int i_iSizeX, int i_iSizeY)
	{
		*o_iArrayIndex = 0;
		*o_iArrayIndex += i_iYCoord * i_iSizeY;
		*o_iArrayIndex += i_iXCoord % i_iSizeY;
		Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::UTILITIES, "From GridIndex:(%i,%i) --> ArrayIndex:%i", i_iXCoord ,i_iYCoord, *o_iArrayIndex);
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