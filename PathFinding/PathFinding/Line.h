#pragma once

#include <SFML/Graphics.hpp>

class Line {
public:
	Line(const sf::Vertex i_pStartPosition, const sf::Vertex i_pEndPosition,const sf::Color i_oColor);

	const sf::Vertex* GetVertex() const { return m_oVertex; }
	void SetPosition(const sf::Vector2f i_oPosition);

private:
	sf::Vertex m_oStartPosition;
	sf::Vertex m_oEndPosition;
	sf::Color m_oColor;

	sf::Vertex m_oVertex[2];
};