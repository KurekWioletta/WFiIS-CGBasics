#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp> 

class Shape {
private:
	sf::Color m_stroke_color;
	sf::Color m_filling_shape_color;
public:
	void setStrokeColor(sf::Color color);
	void setFillingShapeColor(sf::Color color);  
	void drawLine(sf::RenderTarget& target);
};