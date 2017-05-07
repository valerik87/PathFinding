#pragma once
#include "SFML\Graphics\RectangleShape.hpp"

class GridTile : public sf::RectangleShape
{
public:
	GridTile()
	{
		SetFillColor();
	}
protected:
	virtual void SetFillColor(){setFillColor(m_oColor);}

	sf::Color m_oColor = sf::Color::Magenta;
};