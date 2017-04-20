#pragma once


namespace PathFindingStructs
{
	struct PathFindingInput
	{
		//Start position
		int iStartX;
		int iStartY;

		//Target Position
		int iTargetX;
		int iTargetY;

		//Topology
		unsigned char* pMap;
		//GridSize
		int iMapWidth;
		int iMapHeight;

		//Cell's index defining path
		int*	pOutBuffer;

		//Max solution deep
		int		iOutBufferSize;
	};
}