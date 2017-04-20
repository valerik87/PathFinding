#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

class Button : public RectangleShape {
public:
	Button() {};
	Button(Vector2f size);

	void SetPosition(Vector2f pos);
	void SetFillColor(Color color);
	void SetSize(Vector2f size);

	bool IsMouseClickOn(Vector2i i_iMousePosition) const ;

	RectangleShape& Draw() { return dynamic_cast<RectangleShape&>(*this); }; 
};