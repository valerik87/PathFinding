#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

class Button : public RectangleShape {
public:
	Button() :m_oText(){};
	Button(Vector2f size);

	void SetPosition(Vector2f pos);
	void SetFillColor(Color color);
	void SetSize(Vector2f size);
	void SetText(const char* i_cText);

	bool IsMouseClickOn(Vector2i i_iMousePosition) const ;

	void Draw(sf::RenderWindow& i_oWindow);
private:
	Text m_oText;
	Font m_oFont;
};