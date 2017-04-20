#include <iostream>
#include <SFML/Graphics.hpp>

#include "Graphic.h"
#include "ParserInput.h"
#include "Main.h"

using namespace sf;
using namespace std;
using namespace PathFindingStructs;

//WinSreen
const static float SCREEN_SIZE_X = 810;
const static float SCREEN_SIZE_Y = 810;

int main()
{
	ParserInput m_oParseInput;
	Graphic		m_oGraphic;

	sf::RenderWindow m_oWindow(sf::VideoMode(SCREEN_SIZE_X, SCREEN_SIZE_Y), "Path Finding!");
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
							//Calculate path finding
						}
					}
				}
				m_oGraphic.UpdateGraphic();
			}
		}
	}

	return 0;
}