#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Line.h"
#include "PathFindingInput.h"

using namespace PathFindingStructs;
using namespace sf;

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
	const float SCREEN_SIZE_X = 810;
	const float SCREEN_SIZE_Y = 810;
	RenderWindow* m_oWindow;

	//Background
	const float  BG_SIZE_X = 190.f;
	const float  BG_SIZE_Y = 190.f;
	sf::RectangleShape		m_oWhiteRect;

	//Generate Button
	const float GENERATE_BUTTON_SIZE_X = 65.f;
	const float GENERATE_BUTTON_SIZE_Y = 30.0f;
	Button					m_oGenerate;
};