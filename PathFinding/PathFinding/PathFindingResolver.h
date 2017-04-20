#pragma once
#include "ParserInput.h"
using namespace PathFindingStructs;

class PathFindingResolver
{
public:
	void SetInput(const PathFindingInput* i_oPathFindingInput);
	const int* GetInput();
private:
	int FindPath(	const int nStartX, const int nStartY,
					const int nTargetX, const int nTargetY,
					const unsigned char* pMap, 
					const int nMapWidth, const int nMapHeight,
					int* pOutBuffer, const int nOutBufferSize);

	int* m_vOutBuffer;
	PathFindingInput* m_oPathfindingInput;
};