#include <SFML/Graphics.hpp>
#include "Line.h"
#include "Button.h"
#include <iostream>
using namespace sf;
using namespace std;

int main()
{
	//WinSreen
	const float SCREEN_SIZE_X = 810;
	const float SCREEN_SIZE_Y = 810;
	sf::RenderWindow m_oWindow(sf::VideoMode(SCREEN_SIZE_X, SCREEN_SIZE_Y), "Path Finding!");


	//Background
	const float  BG_SIZE_X = 190.f;
	const float  BG_SIZE_Y = 190.f;
	sf::Vector2f			m_vWhiteBGSize(BG_SIZE_X, BG_SIZE_Y);
	sf::RectangleShape		m_oWhiteRect(m_vWhiteBGSize);
	sf::Vector2f			m_vWhiteBGOrigin(SCREEN_SIZE_X / 2 - BG_SIZE_X / 2, SCREEN_SIZE_Y / 2 - BG_SIZE_Y / 2);
	m_oWhiteRect.setPosition(m_vWhiteBGOrigin);	


	//Generate Button
	const float GENERATE_BUTTON_SIZE_X = 65.f;
	const float GENERATE_BUTTON_SIZE_Y = 30.0f;
	sf::Vector2f			m_vGreenBGSize(GENERATE_BUTTON_SIZE_X, GENERATE_BUTTON_SIZE_Y);
	Button					m_oGenerate(m_vGreenBGSize);
	sf::Vector2f			m_vGreenBGOrigin(SCREEN_SIZE_X /2 - GENERATE_BUTTON_SIZE_X /2, SCREEN_SIZE_Y*0.9f);
	m_oGenerate.SetPosition(m_vGreenBGOrigin);
	m_oGenerate.SetFillColor(Color::Green);


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
				if (m_oGenerate.IsMouseClickOn(m_oLocalPosition))
				{
					cout << "GENERATE!" << endl;
				}
			}
		}

		//CLEAN WINDOW
		m_oWindow.clear();

		//Draw White Background
		m_oWindow.draw(m_oWhiteRect);
		//Green Button
		m_oWindow.draw(m_oGenerate.Draw());

		//Draw Red Grid
		const float TILE_SIZE = 10.0f;
		for (int i = 0; i < 20; ++i)
		{
			//RedLine Vertical
			sf::Vertex m_oStart		(sf::Vector2f(m_vWhiteBGOrigin.x + TILE_SIZE*i, m_vWhiteBGOrigin.y));
			sf::Vertex m_oEnd		(sf::Vector2f(m_vWhiteBGOrigin.x + TILE_SIZE*i, m_vWhiteBGOrigin.y + BG_SIZE_Y));

			Line LineV(m_oStart, m_oEnd, sf::Color::Red);
			m_oWindow.draw(LineV.GetVertex(), 2, sf::Lines);

			//RedLine Horizontal
			sf::Vertex m_oStart2	(sf::Vector2f(m_vWhiteBGOrigin.x , m_vWhiteBGOrigin.y+ TILE_SIZE*i));
			sf::Vertex m_oEnd2		(sf::Vector2f((SCREEN_SIZE_X / 2) + (BG_SIZE_X/2) , m_vWhiteBGOrigin.y + TILE_SIZE * i));
			
			Line LineH(m_oStart2, m_oEnd2, sf::Color::Red);
			m_oWindow.draw(LineH.GetVertex(), 2, sf::Lines);
		}
		
		m_oWindow.display();
	}

	return 0;
}