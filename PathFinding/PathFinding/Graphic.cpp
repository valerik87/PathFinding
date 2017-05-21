#include "Graphic.h"
#include "PathFindingInput.h"
#include "Utilities.h"


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

void Graphic::SetSolution(const PathFindingOutput* const i_pGridOutput)
{
	if (i_pGridOutput != nullptr && i_pGridOutput->pOutBuffer != nullptr)
	{
		if (i_pGridOutput->iSize != -1)
		{		
			m_oPathTiles.clear();
			m_oPathTiles.resize(i_pGridOutput->iSize);

			int iCount = 0;
			//using -1 as end path, this because shortest path can be shorter than buffer size
			while (iCount < i_pGridOutput->iSize && i_pGridOutput->pOutBuffer[iCount] != -1)
			{
				using namespace Utilities;
				int X = 0;
				int Y = 0;
				GetGridIndexFromArrayIndex(i_pGridOutput->pOutBuffer[iCount], &X, &Y, m_iMapWidth, m_iMapHeight);
	
				sf::Vector2f	m_vPathTileSize(TILE_SIZE, TILE_SIZE);
				m_oPathTiles[iCount].setSize(m_vPathTileSize);
				m_oPathTiles[iCount].setPosition(GetGridPositionV2f(X, Y));

				++iCount;
			}
			m_bDrawSolution = true;
		}
		else
		{
			cout << "Graphic::SetSolution GridOutput size = -1" << endl;
		}		
		
	}
	else
	{
		cout << "Graphic::SetSolution PathFindingOutput or GridOutput nullptr" << endl;
	}
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
	//Draw Target Tile
	m_oWindow->draw(m_oTargetTile);

	//draw Obstacles Tiles
	for (int i = 0; i < m_oObstacles.size(); ++i)
	{
		m_oWindow->draw(m_oObstacles[i]);
	}

	//draw Path Tiles
	if (m_bDrawSolution)
	{
		for (int i = 0; i < m_oPathTiles.size(); i++)
		{
			m_oWindow->draw(m_oPathTiles[i]);
		}
	}

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
	m_iMapWidth =	i_pGridInput->iMapWidth;
	m_iMapHeight =	i_pGridInput->iMapHeight;
	//Set Background
	BG_SIZE_X = m_iMapWidth		*	TILE_SIZE;
	BG_SIZE_Y = m_iMapHeight	*	TILE_SIZE;

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
	m_oStartTile.setPosition(GetGridPositionV2f(i_pGridInput->iStartX, i_pGridInput->iStartY));

	//Set Draw TargetTile
	sf::Vector2f	m_vTargetTileSize(TILE_SIZE, TILE_SIZE);
	m_oTargetTile.setSize(m_vTargetTileSize);
	m_oTargetTile.setPosition(GetGridPositionV2f(i_pGridInput->iTargetX, i_pGridInput->iTargetY));

	//RedLine Vertical
	m_oVerticalLines.clear();
	m_oVerticalLines.resize(m_iMapWidth +1);
	for (int i = 0; i < m_oVerticalLines.size(); ++i)
	{
		sf::Vertex m_oStart(sf::Vector2f(m_oWhiteRect.getPosition().x + TILE_SIZE*i, m_oWhiteRect.getPosition().y));
		sf::Vertex m_oEnd(sf::Vector2f(m_oWhiteRect.getPosition().x + TILE_SIZE*i, m_oWhiteRect.getPosition().y + BG_SIZE_Y));

		Line line = Line(m_oStart, m_oEnd);
		m_oVerticalLines[i] = line;

	}
	//RedLine Horizontal
	m_oHorizontalLines.clear();
	m_oHorizontalLines.resize(m_iMapHeight + 1);
	for (int i = 0; i < m_oHorizontalLines.size(); ++i)
	{
		sf::Vertex m_oStart2(sf::Vector2f(	m_oWhiteRect.getPosition().x,			m_oWhiteRect.getPosition().y + TILE_SIZE * i));
		sf::Vertex m_oEnd2(sf::Vector2f(	(SCREEN_SIZE_X / 2) + (BG_SIZE_X / 2),	m_oWhiteRect.getPosition().y + TILE_SIZE * i));

		Line line2 = Line(m_oStart2, m_oEnd2);
		m_oHorizontalLines[i] = line2;
	}

	//Obstacles Discovery and Generation	
	int iCount = 0;
	for (int i = 0; i_pGridInput->pMap[i] != '\0'; ++i)
	{
		if (i_pGridInput->pMap[i] == '0')
		{
			++iCount;
			cout << "At ArrayIndex " << i << " founded a zero" << endl;			
		}
	}
	m_oObstacles.clear();
	m_oObstacles.resize(iCount);
	for (int i = 0, j = 0; i_pGridInput->pMap[i] != '\0'; ++i)
	{
		if (i_pGridInput->pMap[i] == '0')
		{
			using namespace Utilities;
			int X = 0;
			int Y = 0;
			GetGridIndexFromArrayIndex(i, &X, &Y, m_iMapWidth, m_iMapHeight);
			sf::Vector2f	m_vObstacleTileSize(TILE_SIZE, TILE_SIZE);
			m_oObstacles[j].setSize(m_vObstacleTileSize);
			m_oObstacles[j].setPosition(GetGridPositionV2f(X,Y));
			++j;
		}
	}

}

sf::Vector2f Graphic::GetGridPositionV2f(int i_iX, int i_iY)
{
	return sf::Vector2f((SCREEN_SIZE_X / 2) - (BG_SIZE_X / 2) + TILE_SIZE*i_iX, (SCREEN_SIZE_Y / 2) - (BG_SIZE_Y / 2) + TILE_SIZE*i_iY);
}