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

		//Max solution deep
		int		iOutBufferSize;

		PathFindingInput& operator=(const PathFindingInput* const i_pPathFindingInput)
		{
			this->iStartX = i_pPathFindingInput->iStartX;
			this->iStartY = i_pPathFindingInput->iStartY;
			this->iTargetX = i_pPathFindingInput->iTargetX;
			this->iTargetY = i_pPathFindingInput->iTargetY;
			memcpy(&this->pMap, &i_pPathFindingInput->pMap, sizeof(i_pPathFindingInput->pMap));
			this->iMapWidth = i_pPathFindingInput->iMapWidth;
			this->iMapHeight = i_pPathFindingInput->iMapHeight;
			this->iOutBufferSize = i_pPathFindingInput->iOutBufferSize;
			return *this;
		}
	};

	struct PathFindingOutput
	{
		//Cell's index defining path
		int*	pOutBuffer;
		int		iSize;
	};
}