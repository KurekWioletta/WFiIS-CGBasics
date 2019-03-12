#include "Shape.h"
 
void Shape::setStrokeColor(sf::Color color) {
	m_stroke_color = color;
}

void Shape::setFillingShapeColor(sf::Color color) {
	m_filling_shape_color = color;
}

void Shape::drawLine(sf::RenderTarget& target) {
}
