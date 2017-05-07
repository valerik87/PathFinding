#pragma once
#include "GridTile.h"

class PathTile : public GridTile
{
public:
	PathTile()
	{
		m_oColor = m_oOverrideColor;
		SetFillColor();
	};
private:
	sf::Color m_oOverrideColor = sf::Color::Green;
};