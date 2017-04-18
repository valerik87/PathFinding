#include "ParserInput.h"
#include <iostream>
using namespace std;

#ifndef XMLCheckResult
	#define XML_CHECK_RESULT(a_eResult) if (a_eResult != XML_SUCCESS) { cout << "Error: " << a_eResult << endl; return a_eResult; }
#endif

bool ParserInput::ReadInput()
{
	cout << "\nReading Input" << endl;

	m_oDoc.LoadFile(m_cPath);
	XML_CHECK_RESULT(m_oDoc.Error());

	XMLNode * pRoot = m_oDoc.FirstChild();
	if (pRoot)
	{
		//START_POS
		XMLElement * pStartPosX = pRoot->FirstChildElement("StartPosX");
		if (pStartPosX)
		{
			int iOutInt;
			XML_CHECK_RESULT(pStartPosX->QueryIntText(&iOutInt));
			m_oPathFindingInput.iStartX = iOutInt;
		}	
		else
		{
			cout << "StartPosX invalid?" << endl;
		}

		XMLElement * pStartPosY = pRoot->FirstChildElement("StartPosY");
		if (pStartPosY)
		{
			int iOutInt;
			XML_CHECK_RESULT(pStartPosY->QueryIntText(&iOutInt));
			m_oPathFindingInput.iStartY = iOutInt;
		}
		else
		{
			cout << "StartPosY invalid?" << endl;
		}
		cout << "START_POS: " << m_oPathFindingInput.iStartX << "," << m_oPathFindingInput.iStartY << endl;

		//TARGET_POS
		XMLElement * pTargetPosX = pRoot->FirstChildElement("TargetPosX");
		if (pTargetPosX)
		{
			int iOutInt;
			XML_CHECK_RESULT(pTargetPosX->QueryIntText(&iOutInt));
			m_oPathFindingInput.iTargetX = iOutInt;
		}
		else
		{
			cout << "TargetPosX invalid?" << endl;
		}

		XMLElement * pTargetPosY = pRoot->FirstChildElement("TargetPosY");
		if (pTargetPosY)
		{
			int iOutInt;
			XML_CHECK_RESULT(pTargetPosY->QueryIntText(&iOutInt));
			m_oPathFindingInput.iTargetY = iOutInt;
		}
		else
		{
			cout << "StartPosY invalid?" << endl;
		}
		cout << "TARGET_POS: " << m_oPathFindingInput.iTargetX << "," << m_oPathFindingInput.iTargetY << endl;
	}
	else
	{
		cout << "Input root invalid?" << endl;
	}
	/*if (m_oDoc.ErrorName() != nullptr)
	{
		cout << "Error loading file" << endl;
		return false;
	}*/

	

	return true;
}