#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Line.h"
#include "PathFindingInput.h"

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

	const Button* GetGenerateButton() { return &m_oGenerate; };

private:
	//Window
	const float SCREEN_SIZE_X = 800;
	const float SCREEN_SIZE_Y = 800;
	RenderWindow* m_oWindow;

	//Grid_Inputs
	PathFindingInput* m_PathFindInput;
	float TILE_SIZE = 10.0f;
	vector<Line>	m_oVerticalLines;
	vector<Line>	m_oHorizontalLines;
	sf::RectangleShape		m_oStartTile;

	//Background
	float  BG_SIZE_X = 200.f;
	float  BG_SIZE_Y = 200.f;
	sf::RectangleShape		m_oWhiteRect;

	//Generate Button
	const float GENERATE_BUTTON_SIZE_X = 65.f;
	const float GENERATE_BUTTON_SIZE_Y = 30.0f;
	Button					m_oGenerate;
};