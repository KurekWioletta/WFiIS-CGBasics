#include "Circle.h"

Circle::Circle(float x, float y)
{
	m_circle = new sf::CircleShape(125);
	m_circle->setPosition(x, y);

	m_colorPixels = new sf::Uint8[250 * 250 * 4];
	m_texture.create(250, 250);
	m_circle->setTexture(&m_texture);
}

Circle::~Circle()
{
	delete m_circle;
	delete m_colorPixels;
}

void Circle::refresh()
{
	m_texture.update(m_colorPixels);
}

sf::CircleShape& Circle::getCircle() const
{
	return *m_circle;
}

void Circle::updateTexture()
{
}