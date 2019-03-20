#include "RGBCircle.h"
 
RGBCircle::RGBCircle(float x, float y) : Circle(x, y)
{
	float r, g, b, radius, angle;
	for (int i = -125; i < 125; i++) {
		for (int j = -125; j < 125; j++) {
			radius = std::sqrt(static_cast<float>(i * i + j * j));
			angle = std::fmodf(std::atan2f(static_cast<float>(j), static_cast<float>(i)) * 180.0f / static_cast<float>(3.141592) + 180.0f, 360.0f);

			r = radius * 0.008f * 255.0f;
			g = angle / 360.0f * 255.0f;
			b = RangeInput::getSelectedValue() * 255.0f;

			if (radius <= 125.0f)
				draw_to_color_pixels(125 - i, 125 + j, r, g, b);
		}
	}
	refresh();
}

void RGBCircle::updateTexture()
{
	float bValue = RangeInput::getSelectedValue() * 255.0f;
	for (unsigned i = 0; i < 250; ++i)
		for (unsigned j = 0; j < 250; ++j)
			m_colorPixels[4 * (j * 250 + i) + 2] = static_cast<sf::Uint8>(bValue);
	refresh();
}