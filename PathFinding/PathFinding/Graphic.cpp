#include "Graphic.h"
#include "PathFindingInput.h"


//WinSreen
void Graphic::InitGraphic(sf::RenderWindow* i_oWindow)
{
	m_oWindow = i_oWindow;

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

	//Draw Generate button
	m_oWindow->draw(m_oGenerate.Draw());

	//Draw White Background
	m_oWindow->draw(m_oWhiteRect);
	//Draw Start Tile
	m_oWindow->draw(m_oStartTile);

	//Draw Grid
	for (int i = 0; i < m_oVerticalLines.size(); i++)
	{
		m_oWindow->draw(m_oVerticalLines[i].GetVertex(), 2, sf::Lines);
	}
	for (int i = 0; i < m_oHorizontalLines.size(); i++)
	{
		m_oWindow->draw(m_oHorizontalLines[i].GetVertex(), 2, sf::Lines);
	}

	m_oWindow->display();
}

void Graphic::SetGridParams(const PathFindingInput* i_pGridInput)
{
	//Set Background
	BG_SIZE_X = i_pGridInput->iMapWidth		*	TILE_SIZE;
	BG_SIZE_Y = i_pGridInput->iMapHeight	*	TILE_SIZE;

	sf::Vector2f	m_vWhiteBGSize(BG_SIZE_X, BG_SIZE_Y);
	m_oWhiteRect.setSize(m_vWhiteBGSize);
	sf::Vector2f	m_vWhiteBGOrigin(SCREEN_SIZE_X / 2 - BG_SIZE_X / 2, SCREEN_SIZE_Y / 2 - BG_SIZE_Y / 2);
	m_oWhiteRect.setPosition(m_vWhiteBGOrigin);

	//Set Generate Button
	sf::Vector2f	m_vGreenBGSize(GENERATE_BUTTON_SIZE_X, GENERATE_BUTTON_SIZE_Y);
	m_oGenerate.SetSize(m_vGreenBGSize);
	sf::Vector2f	m_vGreenBGOrigin(SCREEN_SIZE_X / 2 - GENERATE_BUTTON_SIZE_X / 2, SCREEN_SIZE_Y*0.9f);
	m_oGenerate.SetPosition(m_vGreenBGOrigin);
	m_oGenerate.SetFillColor(Color::Green);

	//Set Draw StartTile
	sf::Vector2f	m_vStartTileSize(TILE_SIZE, TILE_SIZE);
	m_oStartTile.setSize(m_vStartTileSize);
	m_oStartTile.setPosition(m_vWhiteBGOrigin);

	//Defines Lines
	//RedLine Vertical
	m_oVerticalLines.clear();
	m_oVerticalLines.resize(i_pGridInput->iMapWidth +1);
	
	for (int i = 0; i < m_oVerticalLines.size(); ++i)
	{
		sf::Vertex m_oStart(sf::Vector2f(m_oWhiteRect.getPosition().x + TILE_SIZE*i, m_oWhiteRect.getPosition().y));
		sf::Vertex m_oEnd(sf::Vector2f(m_oWhiteRect.getPosition().x + TILE_SIZE*i, m_oWhiteRect.getPosition().y + BG_SIZE_Y));

		Line line = Line(m_oStart, m_oEnd);
		m_oVerticalLines[i] = line;

	}
	//RedLine Horizontal
	m_oHorizontalLines.clear();
	m_oHorizontalLines.resize(i_pGridInput->iMapHeight + 1);
	for (int i = 0; i < m_oHorizontalLines.size(); ++i)
	{
		sf::Vertex m_oStart2(sf::Vector2f(	m_oWhiteRect.getPosition().x,			m_oWhiteRect.getPosition().y + TILE_SIZE * i));
		sf::Vertex m_oEnd2(sf::Vector2f(	(SCREEN_SIZE_X / 2) + (BG_SIZE_X / 2),	m_oWhiteRect.getPosition().y + TILE_SIZE * i));

		Line line2 = Line(m_oStart2, m_oEnd2);
		m_oHorizontalLines[i] = line2;
	}
}