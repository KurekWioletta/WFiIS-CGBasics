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
/*


void CMYCircle::updateTexture()
{
	//std::cout << "lololo" << std::endl;
}

void HSVCircle::updateTexture()
{
	//std::cout << "lololo" << std::endl;
}

void HSLCircle::updateTexture()
{
	//std::cout << "lololo" << std::endl;
}*/
/*
RGBCircle::RGBCircle(float x, float y) : Circle(x, y)
{
	for (int i = -125; i < 125; i++) {
		for (int j = -125; j < 125; j++) {
			float radius = std::sqrt(static_cast<float>(i * i + j * j));
			float angle = std::fmodf(std::atan2f(static_cast<float>(j), static_cast<float>(i)) * 180.0f / static_cast<float>(3.141592) + 180.0f, 360.0f);

			float r = radius * 0.008f * 255.0f;
			float g = angle / 360.0f * 255.0f;
			float b = RangeInput::getSelectedValue() * 255.0f;

			if (radius <= 125.0f)
				draw_to_color_pixels(125 - i, 125 + j, r, g, b, m_colorPixels);
		}
	}
	refresh();
}

void RGBCircle::updateTexture()
{
	for (unsigned i = 0; i < 250; ++i)
		for (unsigned j = 0; j < 250; ++j)
			m_colorPixels[4 * (j * 250 + i) + 2] = static_cast<sf::Uint8>(255.0f - RangeInput::getSelectedValue() * 255.0f);
	refresh();
}

CMYCircle::CMYCircle(float x, float y) : Circle(x, y)
{
	for (int i = -125; i < 125; i++) {
		for (int j = -125; j < 125; j++) {
			float radius = std::sqrt(static_cast<float>(i * i + j * j));
			float angle = std::fmodf(std::atan2f(static_cast<float>(j), static_cast<float>(i)) * 180.0f / static_cast<float>(3.141592) + 180.0f, 360.0f);

			float c = radius * 0.008f;
			float m = angle / 360.0f;
			float y = RangeInput::getSelectedValue() * 255.0f;

			if (radius <= 125.0f)
				draw_to_color_pixels(125 - i, 125 + j, c, m, y, m_colorPixels);
		}
	}
	refresh();
}

void CMYCircle::updateTexture()
{
	for (unsigned i = 0; i < 250; ++i)
		for (unsigned j = 0; j < 250; ++j)
			m_colorPixels[4 * (j * 250 + i) + 2] = static_cast<sf::Uint8>(255.0f - RangeInput::getSelectedValue() * 255.0f);
	refresh();
}

*/