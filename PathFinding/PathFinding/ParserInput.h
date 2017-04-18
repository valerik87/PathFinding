#pragma once
#include "tinyxml2.h"
using namespace tinyxml2;

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

class ParserInput
{
public:
	bool ReadInput();
	PathFindingInput m_oPathFindingInput;
private:
	const char* m_cPath = "..\\Input.xml";
	XMLDocument m_oDoc;
};