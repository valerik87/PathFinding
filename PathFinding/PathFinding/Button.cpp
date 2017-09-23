#include "Button.h"

Button::Button(Vector2f size):
	RectangleShape(size)
{}

void Button::Draw(sf::RenderWindow& i_oWindow)
{
	i_oWindow.draw(*this);
	i_oWindow.draw(m_oText);
}

void Button::SetPosition(Vector2f pos)
{
	setPosition(pos);
	m_oText.setPosition(pos);
}
void Button::SetFillColor(Color color)
{
	setFillColor(color);
}

void Button::SetSize(Vector2f size)
{
	setSize(size);
}

void Button::SetText(const char* i_cText)
{
	
	bool b = m_oFont.loadFromFile("Font\\arial.ttf");
	m_oText.setFont(m_oFont);
	m_oText.setString(i_cText);
	m_oText.setCharacterSize(30);
	
	m_oText.setFillColor(sf::Color::Red);
	m_oText.setOutlineColor(sf::Color::Red);
	m_oText.setStyle(sf::Text::Bold);
}

bool Button::IsMouseClickOn(Vector2i i_iMousePosition) const
{
	Vector2f m_oOriginPos = RectangleShape::getPosition();
	Vector2f m_oSize = m_oOriginPos+RectangleShape::getSize();
	return  i_iMousePosition.x >= m_oOriginPos.x && i_iMousePosition.x <= m_oSize.x && i_iMousePosition.y >= m_oOriginPos.y && i_iMousePosition.y <= m_oSize.y;
}
