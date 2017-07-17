#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>

#include "Graphic.h"
#include "ParserInput.h"
#include "PathFindingResolver.h"
#include "Main.h"

using namespace sf;
using namespace std;
using namespace PathFindingStructs;

//WinSreen
const static float SCREEN_SIZE_X = 810;
const static float SCREEN_SIZE_Y = 810;

#define THREAD_TEST
#undef THREAD_TEST

DWORD WINAPI ThreadTest(LPVOID lpParameter)
{
	unsigned int& myCounter = *((unsigned int*)lpParameter);
	while (myCounter < 0xFFFFFFFF) ++myCounter;
	cout << "END: " << myCounter << endl;
	return 0;
};

int main()
{
#ifdef THREAD_TEST
	using namespace std;

	unsigned int myCounter = 0;
	DWORD myThreadID;
	HANDLE myHandle = CreateThread(0, 0, ThreadTest, &myCounter , 0, &myThreadID);
	char myChar = ' ';
	while (myChar != 'q') {
		cout << myCounter << endl;
		myChar = getchar();
	}
	CloseHandle(myHandle);
#else
	ParserInput			m_oParseInput;
	Graphic				m_oGraphic;
	PathFindingResolver m_oPathFindingResolver;

	sf::RenderWindow m_oWindow(sf::VideoMode(SCREEN_SIZE_X, SCREEN_SIZE_Y), "Path Finding!");
	m_oWindow.setVerticalSyncEnabled(true);
	m_oGraphic.InitGraphic(&m_oWindow);

	if (m_oGraphic.GetGenerateButton())
	{
		while (m_oWindow.isOpen())
		{
			sf::Event m_oEvent;
			while (m_oWindow.pollEvent(m_oEvent))
			{
				if (m_oEvent.type == sf::Event::Closed)
					m_oWindow.close();

				//MOUSE
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{

					// left mouse button is pressed
					sf::Vector2i m_oLocalPosition = sf::Mouse::getPosition(m_oWindow);
					cout << "Left Mouse Pressed in coord (" << m_oLocalPosition.x << " , " << m_oLocalPosition.y << ")" << endl;
				
					if (m_oGraphic.GetGenerateButton()->IsMouseClickOn(m_oLocalPosition))
					{
						const PathFindingStructs::PathFindingInput* ioPathFindingInput = m_oParseInput.ReadInput();
						if (ioPathFindingInput != nullptr)
						{
							m_oGraphic.SetGridParams(ioPathFindingInput);
							const PathFindingOutput* pPathFIndingOutput = m_oPathFindingResolver.GetSolution(ioPathFindingInput);
							m_oGraphic.SetSolution(pPathFIndingOutput);
							//Calculate path finding
						}
					}
				}
				m_oGraphic.UpdateGraphic();
			}
			
		}
	}
#endif // else #ifdef THREAD_TEST
	return 0;
}

#undef THREAD_TEST