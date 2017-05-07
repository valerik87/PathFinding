#pragma once
#include "GridTile.h"

class StartTile : public GridTile
{
public:
	StartTile()
	{
		m_oColor = m_oOverrideColor;
		SetFillColor();
	};
private:
	sf::Color m_oOverrideColor = sf::Color::Blue;
};