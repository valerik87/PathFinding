#include "Graphic.h"
#include "PathFindingInput.h"


//WinSreen
void Graphic::InitGraphic(sf::RenderWindow* i_oWindow)
{
	m_oWindow = i_oWindow;

	//Background
	sf::Vector2f	m_vWhiteBGSize(BG_SIZE_X, BG_SIZE_Y);
	m_oWhiteRect.setSize(m_vWhiteBGSize);
	sf::Vector2f	m_vWhiteBGOrigin(SCREEN_SIZE_X / 2 - BG_SIZE_X / 2, SCREEN_SIZE_Y / 2 - BG_SIZE_Y / 2);
	m_oWhiteRect.setPosition(m_vWhiteBGOrigin);

	//Generate Button
	sf::Vector2f	m_vGreenBGSize(GENERATE_BUTTON_SIZE_X, GENERATE_BUTTON_SIZE_Y);
	m_oGenerate.SetSize(m_vGreenBGSize);
	sf::Vector2f	m_vGreenBGOrigin(SCREEN_SIZE_X / 2 - GENERATE_BUTTON_SIZE_X / 2, SCREEN_SIZE_Y*0.9f);
	m_oGenerate.SetPosition(m_vGreenBGOrigin);
	m_oGenerate.SetFillColor(Color::Green);
}

void Graphic::UpdateGraphic()
{
	//CLEAN WINDOW
	m_oWindow->clear();

	//Draw White Background
	m_oWindow->draw(m_oWhiteRect);
	//Green Button
	m_oWindow->draw(m_oGenerate.Draw());

	//Draw Red Grid
	const float TILE_SIZE = 10.0f;
	for (int i = 1; i < 20; ++i)
	{
		//RedLine Vertical
		sf::Vertex m_oStart(sf::Vector2f(	m_oWhiteRect.getPosition().x + TILE_SIZE*i,	m_oWhiteRect.getPosition().y));
		sf::Vertex m_oEnd(sf::Vector2f(		m_oWhiteRect.getPosition().x + TILE_SIZE*i,	m_oWhiteRect.getPosition().y + BG_SIZE_Y));

		Line LineV(m_oStart, m_oEnd, sf::Color::Red);
		m_oWindow->draw(LineV.GetVertex(), 2, sf::Lines);

		//RedLine Horizontal
		sf::Vertex m_oStart2(sf::Vector2f(	m_oWhiteRect.getPosition().x,				m_oWhiteRect.getPosition().y + TILE_SIZE * i));
		sf::Vertex m_oEnd2(sf::Vector2f(	(SCREEN_SIZE_X / 2) + (BG_SIZE_X / 2),		m_oWhiteRect.getPosition().y + TILE_SIZE * i));

		Line LineH(m_oStart2, m_oEnd2, sf::Color::Red);
		m_oWindow->draw(LineH.GetVertex(), 2, sf::Lines);
	}

	m_oWindow->display();
}

void Graphic::SetGridParams(const PathFindingInput* i_pGridInput)
{

}