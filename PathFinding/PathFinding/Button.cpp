#include "Button.h"

Button::Button(Vector2f size):
	RectangleShape(size)
{

}

void Button::SetPosition(Vector2f pos)
{
	setPosition(pos);
}
void Button::SetFillColor(Color color)
{
	setFillColor(color);
}

bool Button::IsMouseClickOn(Vector2i i_iMousePosition) const
{
	Vector2f m_oOriginPos = RectangleShape::getPosition();
	Vector2f m_oSize = m_oOriginPos+RectangleShape::getSize();
	return  i_iMousePosition.x >= m_oOriginPos.x && i_iMousePosition.x <= m_oSize.x && i_iMousePosition.y >= m_oOriginPos.y && i_iMousePosition.y <= m_oSize.y;
}
