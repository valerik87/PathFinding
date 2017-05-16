#pragma once
#include "SFML\Graphics\RectangleShape.hpp"

class ObstacleTile : public sf::RectangleShape
{
public:
	ObstacleTile()
	{
		SetFillColor();
	}
protected:
	virtual void SetFillColor() { setFillColor(m_oColor); }

	sf::Color m_oColor = sf::Color::Red;
};