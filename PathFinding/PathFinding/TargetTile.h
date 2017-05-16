#pragma once
#include "SFML\Graphics\RectangleShape.hpp"

class TargetTile : public sf::RectangleShape
{
public:
	TargetTile()
	{
		SetFillColor();
	}
protected:
	virtual void SetFillColor() { setFillColor(m_oColor); }

	sf::Color m_oColor = sf::Color::Yellow;
};