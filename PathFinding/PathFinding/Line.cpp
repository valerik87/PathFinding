#include "Line.h"

Line::Line()
{
	m_oStartPosition = sf::Vector2f(0,0);
	m_oEndPosition = sf::Vector2f(0, 0);
	m_oVertex[0] = sf::Vertex(m_oStartPosition);
	m_oVertex[1] = sf::Vertex(m_oEndPosition);
	m_oVertex[0].color = sf::Color::Red;
	m_oVertex[1].color = sf::Color::Red;
}

Line::Line(const Line& i_oLine)
{
	m_oStartPosition = i_oLine.m_oStartPosition;
	m_oEndPosition = i_oLine.m_oEndPosition;
	m_oVertex[0] = sf::Vertex(m_oStartPosition);
	m_oVertex[1] = sf::Vertex(m_oEndPosition);
	m_oVertex[0].color = sf::Color::Red;
	m_oVertex[1].color = sf::Color::Red;
}

Line::Line(const sf::Vertex i_pStartPosition, const sf::Vertex i_pEndPosition):
	m_oStartPosition(i_pStartPosition),
	m_oEndPosition(i_pEndPosition)
{
	m_oVertex[0] = i_pStartPosition;
	m_oVertex[1] = i_pEndPosition;
	
	m_oVertex[0].color = sf::Color::Red;
	m_oVertex[1].color = sf::Color::Red;
}

Line* Line::operator=(Line& i_oLine)
{
	m_oStartPosition = i_oLine.m_oStartPosition;
	m_oEndPosition = i_oLine.m_oEndPosition;
	m_oVertex[0] = sf::Vertex(m_oStartPosition);
	m_oVertex[1] = sf::Vertex(m_oEndPosition);
	m_oVertex[0].color = sf::Color::Red;
	m_oVertex[1].color = sf::Color::Red;
	return this;
}
