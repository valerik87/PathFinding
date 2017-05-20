#include "PathFindingResolver.h"

#include <iostream>
#include "Utilities.h"

const PathFindingOutput* PathFindingResolver::GetSolution(const PathFindingInput* const i_pPathFindingInput)
{
	m_oPathfindingInput = i_pPathFindingInput;
	m_oPathFindingOutput.pOutBuffer = new int[m_oPathfindingInput.iOutBufferSize];
	
	int iSolutionLength = FindPath
		(
			m_oPathfindingInput.iStartX,
			m_oPathfindingInput.iStartY,
			m_oPathfindingInput.iTargetX,
			m_oPathfindingInput.iTargetY,
			m_oPathfindingInput.pMap,
			m_oPathfindingInput.iMapWidth,
			m_oPathfindingInput.iMapHeight,
			m_oPathFindingOutput.pOutBuffer,
			m_oPathfindingInput.iOutBufferSize
			);
	return &m_oPathFindingOutput;
}

/*
The function must return the length of the shortest path between Start and Target, or −1−1 if no such path exists.
If the shortest path is longer than nOutBufferSize, the calling function might either give up or choose to call FindPath again with a larger output buffer.
*/
int PathFindingResolver::FindPath
(
	const int i_iStartX, const int i_iStartY,
	const int i_iTargetX, const int i_iTargetY,
	const unsigned char* i_pMap,
	const int i_iMapWidth, const int i_iMapHeight,
	int* i_pOutBuffer, const int i_iOutBufferSize
)
{
	//init default return and outputVariable with unfeasable values
	int iStartIndexA = -1;
	*i_pOutBuffer = iStartIndexA;

	//From Start position need to get the list of adjacent obj;
	using namespace Utilities;
	using namespace std;
	GetArrayIndexFromGridIndex(&iStartIndexA,i_iStartX, i_iStartY,i_iMapWidth,i_iMapHeight);
	cout << "StartIndexA: " << iStartIndexA << endl;
	*i_pOutBuffer = iStartIndexA;

	return -1;
}
