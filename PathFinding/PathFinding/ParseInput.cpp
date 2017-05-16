#include "ParserInput.h"
#include <iostream>
using namespace std;

#ifndef XMLCheckResult
	#define XML_CHECK_RESULT(a_eResult) if (a_eResult != XML_SUCCESS) { cout << "Error: " << a_eResult << endl;}
#endif
namespace PathFindingStructs
{

	const PathFindingStructs::PathFindingInput* ParserInput::ReadInput()
	{
		cout << "\nReading Input" << endl;

		m_oDoc.LoadFile(m_cPath);
		m_oError = m_oDoc.ErrorID();
		XML_CHECK_RESULT(m_oError)

		XMLNode * pRoot = m_oDoc.FirstChild();
		if (pRoot)
		{
			ReadStart(pRoot);
			ReadTarget(pRoot);
			ReadGridSize(pRoot);
			ReadBufferSize(pRoot);
			ReadTopology(pRoot);
		}
		else
		{
			cout << "Input root invalid?" << endl;
		}
	
		if (m_oError != XMLError::XML_SUCCESS)
		{
			cout << "Error reading file" << endl;
			return nullptr;
		}
		return &m_oPathFindingInput;
	}

	void ParserInput::ReadStart(const XMLNode* i_pNode)
	{
		const XMLElement * pStartPosX = i_pNode->FirstChildElement("StartPosX");
		if (pStartPosX)
		{
			int iOutInt = -1;
			m_oError = pStartPosX->QueryIntText(&iOutInt);
			XML_CHECK_RESULT(m_oError)
			m_oPathFindingInput.iStartX = iOutInt;
		}
		else
		{
			cout << "StartPosX malformed?" << endl;
		}

		const XMLElement * pStartPosY = i_pNode->FirstChildElement("StartPosY");
		if (pStartPosY)
		{
			int iOutInt = -1;
			m_oError = pStartPosY->QueryIntText(&iOutInt);
			XML_CHECK_RESULT(m_oError);
			m_oPathFindingInput.iStartY = iOutInt;
		}
		else
		{
			cout << "StartPosY malformed?" << endl;
		}
		cout << "START_POS: " << m_oPathFindingInput.iStartX << "," << m_oPathFindingInput.iStartY << endl;
	}

	void ParserInput::ReadTarget(const XMLNode* i_pNode)
	{
		//TARGET_POS
		const XMLElement * pTargetPosX = i_pNode->FirstChildElement("TargetPosX");
		if (pTargetPosX)
		{
			int iOutInt = -1;
			m_oError = pTargetPosX->QueryIntText(&iOutInt);
			XML_CHECK_RESULT(m_oError);
			m_oPathFindingInput.iTargetX = iOutInt;
		}
		else
		{
			cout << "TargetPosX malformed?" << endl;
		}

		const XMLElement * pTargetPosY = i_pNode->FirstChildElement("TargetPosY");
		if (pTargetPosY)
		{
			int iOutInt = -1;
			m_oError = pTargetPosY->QueryIntText(&iOutInt);
			XML_CHECK_RESULT(m_oError);
			m_oPathFindingInput.iTargetY = iOutInt;
		}
		else
		{
			cout << "StartPosY malformed?" << endl;
		}
		cout << "TARGET_POS: " << m_oPathFindingInput.iTargetX << "," << m_oPathFindingInput.iTargetY << endl;
	}

	void ParserInput::ReadGridSize(const XMLNode* i_pNode)
	{
		//MAP_SIZE
		const XMLElement * pMapWidth = i_pNode->FirstChildElement("MapWidth");
		if (pMapWidth)
		{
			int iOutInt = -1;
			m_oError = pMapWidth->QueryIntText(&iOutInt);
			XML_CHECK_RESULT(m_oError);
			m_oPathFindingInput.iMapWidth = iOutInt;
		}
		else
		{
			cout << "MapWidth malformed?" << endl;
		}

		const XMLElement * pMapHeight = i_pNode->FirstChildElement("MapHeight");
		if (pMapHeight)
		{
			int iOutInt = -1;
			m_oError = pMapHeight->QueryIntText(&iOutInt);
			XML_CHECK_RESULT(m_oError);
			m_oPathFindingInput.iMapHeight = iOutInt;
		}
		else
		{
			cout << "MapHeight malformed?" << endl;
		}
		cout << "MAP SIZE(W,H): " << m_oPathFindingInput.iMapWidth << "," << m_oPathFindingInput.iMapHeight << endl;
	}

	void ParserInput::ReadBufferSize(const XMLNode* i_pNode)
	{
		//BUFFER_SIZE
		const XMLElement* pBufferSize = i_pNode->FirstChildElement("BufferSize");
		if (pBufferSize)
		{
			int iOutInt = -1;
			m_oError = pBufferSize->QueryIntText(&iOutInt);
			XML_CHECK_RESULT(m_oError);
			m_oPathFindingInput.iOutBufferSize = iOutInt;
		}
		else
		{
			cout << "BufferSize malformed?" << endl;
		}
		cout << "BUFFER SIZE: " << m_oPathFindingInput.iOutBufferSize << endl;
	}

	void ParserInput::ReadTopology(const XMLNode* i_pNode)
	{
		//TOPOLOGY
		const XMLElement * pMap = i_pNode->FirstChildElement("Map");
		if (pMap)
		{
			//TODO
			const char * pOutChar = pMap->GetText();
			if (pOutChar != nullptr)
			{
				memcpy(&m_oPathFindingInput.pMap, &pOutChar, sizeof(pOutChar));
			}
			else
			{
				cout << "Empty Map?" << endl;
				m_oError = XMLError::XML_ERROR_EMPTY_DOCUMENT;
				XML_CHECK_RESULT(m_oError);
			}
		}
		else
		{
			cout << "Map malformed?" << endl;
		}
		printf("MAP: %s\n", m_oPathFindingInput.pMap);
	}
}