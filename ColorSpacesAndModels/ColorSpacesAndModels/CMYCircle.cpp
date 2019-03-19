#include "CMYCircle.h"

CMYCircle::CMYCircle(float x, float y) : Circle(x, y)
{
	for (int i = -125; i < 125; i++) {
		for (int j = -125; j < 125; j++) {
			float radius = sqrt(static_cast<float>(i * i + j * j));
			float angle = fmodf(atan2f(static_cast<float>(j), static_cast<float>(i)) * 180.0f / static_cast<float>(3.141592) + 180.0f, 360.0f);
			
			// (1 - xRGB) * 255 = xCMY
			float c = (1.0f - radius * 0.008f) * 255.0f; 
			float m = (1.0f - angle / 360.0f) * 255.0f;
			float y = (1.0f - RangeInput::getSelectedValue()) * 255.0f;

			if (radius <= 125.0f)
				draw_to_color_pixels(125 - i, 125 + j, c, m, y);
		}
	}
	refresh();
}

void CMYCircle::updateTexture()
{
	for (unsigned i = 0; i < 250; ++i)
		for (unsigned j = 0; j < 250; ++j)
			m_colorPixels[4 * (j * 250 + i) + 2] = static_cast<sf::Uint8>((1.0f - RangeInput::getSelectedValue()) * 255.0f);
	refresh();
}