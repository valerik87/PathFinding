#include "ParserInput.h"

#include "Logger.h"
#include <iostream>
using namespace std;

namespace PathFindingStructs
{

	const PathFindingStructs::PathFindingInput* ParserInput::ReadInput()
	{
		Clear();
		Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::INPUT_PARSER, "Reading Input");

		m_oDoc.LoadFile(m_cPath);
		m_oError = m_oDoc.ErrorID();
		Logger::GetInstance().Log(Logger::SEVERITY::ERR, Logger::CONTEXT::INPUT_PARSER, "Error: &i", m_oError);

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
			Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::INPUT_PARSER, "Input root invalid?");
		}
	
		if (m_oError != XMLError::XML_SUCCESS)
		{
			Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::INPUT_PARSER, "Error reading file");
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
			Logger::GetInstance().Log(Logger::SEVERITY::ERR, Logger::CONTEXT::INPUT_PARSER, "Error: &i", m_oError);
			m_oPathFindingInput.iStartX = iOutInt;
		}
		else
		{
			Logger::GetInstance().Log(Logger::SEVERITY::ERR, Logger::CONTEXT::INPUT_PARSER, "StartPosX malformed?");
		}

		const XMLElement * pStartPosY = i_pNode->FirstChildElement("StartPosY");
		if (pStartPosY)
		{
			int iOutInt = -1;
			m_oError = pStartPosY->QueryIntText(&iOutInt);
			Logger::GetInstance().Log(Logger::SEVERITY::ERR, Logger::CONTEXT::INPUT_PARSER, "Error: &i", m_oError);
			m_oPathFindingInput.iStartY = iOutInt;
		}
		else
		{
			Logger::GetInstance().Log(Logger::SEVERITY::ERR, Logger::CONTEXT::INPUT_PARSER, "StartPosY malformed?");
		}
		Logger::GetInstance().Log(Logger::SEVERITY::ERR, Logger::CONTEXT::INPUT_PARSER, "START_POS (%i,%i)",m_oPathFindingInput.iStartX,m_oPathFindingInput.iStartY);
	}

	void ParserInput::ReadTarget(const XMLNode* i_pNode)
	{
		//TARGET_POS
		const XMLElement * pTargetPosX = i_pNode->FirstChildElement("TargetPosX");
		if (pTargetPosX)
		{
			int iOutInt = -1;
			m_oError = pTargetPosX->QueryIntText(&iOutInt);
			Logger::GetInstance().Log(Logger::SEVERITY::ERR, Logger::CONTEXT::INPUT_PARSER, "Error: &i", m_oError);
			m_oPathFindingInput.iTargetX = iOutInt;
		}
		else
		{
			Logger::GetInstance().Log(Logger::SEVERITY::ERR, Logger::CONTEXT::INPUT_PARSER, "TargetPosX malformed?");
		}

		const XMLElement * pTargetPosY = i_pNode->FirstChildElement("TargetPosY");
		if (pTargetPosY)
		{
			int iOutInt = -1;
			m_oError = pTargetPosY->QueryIntText(&iOutInt);
			Logger::GetInstance().Log(Logger::SEVERITY::ERR, Logger::CONTEXT::INPUT_PARSER, "Error: &i", m_oError);
			m_oPathFindingInput.iTargetY = iOutInt;
		}
		else
		{
			Logger::GetInstance().Log(Logger::SEVERITY::ERR, Logger::CONTEXT::INPUT_PARSER, "TargetPosY malformed?");
		}
		Logger::GetInstance().Log(Logger::SEVERITY::ERR, Logger::CONTEXT::INPUT_PARSER, "TARGET_POS (%i,%i)", m_oPathFindingInput.iTargetX, m_oPathFindingInput.iTargetY);
	}

	void ParserInput::ReadGridSize(const XMLNode* i_pNode)
	{
		//MAP_SIZE
		const XMLElement * pMapWidth = i_pNode->FirstChildElement("MapWidth");
		if (pMapWidth)
		{
			int iOutInt = -1;
			m_oError = pMapWidth->QueryIntText(&iOutInt);
			Logger::GetInstance().Log(Logger::SEVERITY::ERR, Logger::CONTEXT::INPUT_PARSER, "Error: &i", m_oError);
			m_oPathFindingInput.iMapWidth = iOutInt;
		}
		else
		{
			Logger::GetInstance().Log(Logger::SEVERITY::ERR, Logger::CONTEXT::INPUT_PARSER, "MapWidth malformed?");
		}

		const XMLElement * pMapHeight = i_pNode->FirstChildElement("MapHeight");
		if (pMapHeight)
		{
			int iOutInt = -1;
			m_oError = pMapHeight->QueryIntText(&iOutInt);
			Logger::GetInstance().Log(Logger::SEVERITY::ERR, Logger::CONTEXT::INPUT_PARSER, "Error: &i", m_oError);
			m_oPathFindingInput.iMapHeight = iOutInt;
		}
		else
		{
			Logger::GetInstance().Log(Logger::SEVERITY::ERR, Logger::CONTEXT::INPUT_PARSER, "MapHeight malformed?");
		}
		Logger::GetInstance().Log(Logger::SEVERITY::ERR, Logger::CONTEXT::INPUT_PARSER, "MAP SIZE(W,H):(%i,%i)", m_oPathFindingInput.iMapWidth, m_oPathFindingInput.iMapHeight);
	}

	void ParserInput::ReadBufferSize(const XMLNode* i_pNode)
	{
		//BUFFER_SIZE
		const XMLElement* pBufferSize = i_pNode->FirstChildElement("BufferSize");
		if (pBufferSize)
		{
			int iOutInt = -1;
			m_oError = pBufferSize->QueryIntText(&iOutInt);
			Logger::GetInstance().Log(Logger::SEVERITY::ERR, Logger::CONTEXT::INPUT_PARSER, "Error: &i", m_oError);
			m_oPathFindingInput.iOutBufferSize = iOutInt;
		}
		else
		{
			Logger::GetInstance().Log(Logger::SEVERITY::ERR, Logger::CONTEXT::INPUT_PARSER, "BufferSize malformed?");
		}
		Logger::GetInstance().Log(Logger::SEVERITY::ERR, Logger::CONTEXT::INPUT_PARSER, "BUFFER SIZE: &i", m_oPathFindingInput.iOutBufferSize);
	}

	void ParserInput::ReadTopology(const XMLNode* i_pNode)
	{
		//TOPOLOGY
		const XMLElement * pMap = i_pNode->FirstChildElement("Map");
		if (pMap)
		{
			const char * pOutChar = pMap->GetText();
			if (pOutChar != nullptr)
			{
				char* cpy = const_cast<char*>(pOutChar);	// an alias to iterate through pOutChar without moving pOutChar
				
				int size = strlen(pOutChar);
				char* temp = new char[size];				// this one produces the desired string
				
				pOutChar = temp;							

				while (*cpy != '\0') 
				{
					if (*cpy == '\t' || *cpy == '\n')
						cpy++;
					else
						*temp++ = *cpy++;
				}
				//delete(temp);
				memcpy(&m_oPathFindingInput.pMap, &pOutChar, sizeof(pOutChar));
			}
			else
			{
				m_oError = XMLError::XML_ERROR_EMPTY_DOCUMENT;
				Logger::GetInstance().Log(Logger::SEVERITY::ERR, Logger::CONTEXT::INPUT_PARSER, "Error: &i", m_oError);
			}
		}
		else
		{
			Logger::GetInstance().Log(Logger::SEVERITY::ERR, Logger::CONTEXT::INPUT_PARSER, "Map malformed?");
		}

		Logger::GetInstance().Log(Logger::SEVERITY::ERR, Logger::CONTEXT::INPUT_PARSER, "MAP: %s", m_oPathFindingInput.pMap);
	}

	void ParserInput::Clear()
	{
		m_oDoc.Clear();
		m_oDoc.ClearError();
		m_oError = XMLError::XML_SUCCESS;
		m_oPathFindingInput.Clear();
	}
}