#pragma once
#include "tinyxml2.h"
#include "PathFindingInput.h"
using namespace tinyxml2;

namespace PathFindingStructs
{
	class ParserInput
	{
	public:
		const PathFindingInput* ReadInput();
		PathFindingInput m_oPathFindingInput;
	private:
		const char* m_cPath = "..\\Input.xml";
		XMLDocument m_oDoc;
		XMLError	m_oError;

		void ReadStart(const XMLNode* i_pNode);
		void ReadTarget(const XMLNode* i_pNode);
		void ReadGridSize(const XMLNode* i_pNode);
		void ReadBufferSize(const XMLNode* i_pNode);
		void ReadTopology(const XMLNode* i_pNode);
	};
}