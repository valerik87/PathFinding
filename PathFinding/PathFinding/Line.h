#pragma once

#include <SFML/Graphics.hpp>

class Line {
public:
	Line();
	Line(const sf::Vertex i_pStartPosition, const sf::Vertex i_pEndPosition);
	Line(const Line& other);

	Line* operator=(Line& other);

	const sf::Vertex* GetVertex() const { return m_oVertex; }

private:
	sf::Vertex m_oStartPosition;
	sf::Vertex m_oEndPosition;
	sf::Color m_oColor;

	sf::Vertex m_oVertex[2];
};
