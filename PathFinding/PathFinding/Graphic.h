#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include <iostream>
#include "Line.h"
#include "ObstacleTile.h"
#include "PathFindingInput.h"
#include "PathTile.h"
#include "StartTile.h"
#include "TargetTile.h"

using namespace PathFindingStructs;
using namespace sf;
using namespace std;

class Graphic
{

public:
	Graphic() {};

	void InitGraphic(sf::RenderWindow* i_oWindow);
	void UpdateGraphic();
	void SetGridParams(const PathFindingInput* i_pGridInput);
	void SetSolution(const PathFindingOutput* i_pGridOutut);

	const Button* GetGenerateButton() { return &m_oGenerate; };

private:

	sf::Vector2f GetGridPositionV2f(int i_iX, int i_Y);

	//Grid_Inputs
	int m_iMapWidth = 0;
	int m_iMapHeight = 0;
	
	//Window
	const float SCREEN_SIZE_X = 800;
	const float SCREEN_SIZE_Y = 800;
	RenderWindow* m_oWindow;

	//TILES
	float TILE_SIZE = 10.0f;
	//Start
	StartTile		m_oStartTile;
	//Target
	TargetTile		m_oTargetTile;
	//Path
	vector<PathTile> m_oPathTiles;
	//Obstacles
	vector<ObstacleTile> m_oObstacles;

	//LINES
	vector<Line>	m_oVerticalLines;
	vector<Line>	m_oHorizontalLines;

	//Background
	float  BG_SIZE_X = 200.f;
	float  BG_SIZE_Y = 200.f;
	sf::RectangleShape	m_oWhiteRect;

	//Generate Button
	const float GENERATE_BUTTON_SIZE_X = 65.f;
	const float GENERATE_BUTTON_SIZE_Y = 30.0f;
	Button m_oGenerate;

	bool	m_bDrawSolution;
};