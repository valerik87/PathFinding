#pragma once

#include <iostream>
#include "ParserInput.h"


using namespace PathFindingStructs;
using namespace std;

class PathFindingResolver
{
public:
	PathFindingResolver():
		m_oPathFindingOutput()
	{};
	const PathFindingOutput* GetSolution(const PathFindingInput* const i_pPathFindingInput);
private:
	int FindPath(	const int i_iStartX, const int i_iStartY,
					const int i_iTargetX, const int i_iTargetY,
					const unsigned char* i_pMap, 
					const int i_iMapWidth, const int i_iMapHeight,
					int* i_pOutBuffer, const int i_iOutBufferSize);

	PathFindingInput		m_oPathfindingInput;
	PathFindingOutput		m_oPathFindingOutput;

//	void GetValidNeighborhood(const vector io_pNeighborhood);
};