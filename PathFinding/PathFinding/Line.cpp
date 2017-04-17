#include "Line.h"

Line::Line(const sf::Vertex i_pStartPosition, const sf::Vertex i_pEndPosition, const sf::Color i_oColor):
	m_oStartPosition(i_pStartPosition),
	m_oEndPosition(i_pEndPosition),
	m_oColor(i_oColor)
{
	m_oVertex[0] = i_pStartPosition;
	m_oVertex[1] = i_pEndPosition;
	
	m_oVertex[0].color = i_oColor;
	m_oVertex[1].color = i_oColor;
}

void Line::SetPosition(const sf::Vector2f i_oPosition)
{
	m_oStartPosition.position += i_oPosition;
	m_oStartPosition.position += i_oPosition;
}
