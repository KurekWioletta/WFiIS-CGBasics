#include "HSLCircle.h"

HSLCircle::HSLCircle(float x, float y) : Circle(x, y)
{
	float radius, angle;
	for (int i = -125; i < 125; i++) {
		for (int j = -125; j < 125; j++) {
			radius = sqrt(static_cast<float>(i * i + j * j));
			angle = fmodf(atan2f(static_cast<float>(j), static_cast<float>(i)) * 180.0f / static_cast<float>(3.141592) + 180.0f, 360.0f);

			m_HSL[0] = m_H[i + 125][j + 125] = angle;
			m_HSL[1] = m_S[i + 125][j + 125] = radius * 0.008f;
			m_HSL[2] = RangeInput::getSelectedValue();
			 
			convertToRGB(i + 125, j + 125);

			if (radius <= 125.0f)
				draw_to_color_pixels(125 - i, 125 + j, m_RGB[0], m_RGB[1], m_RGB[2]);
		}
	}
	refresh();
}

void HSLCircle::updateTexture()
{
	float radius;
	m_HSL[2] = RangeInput::getSelectedValue();
	for (unsigned i = 0; i < 250; i++) {
		for (unsigned j = 0; j < 250; j++) {
			radius = sqrt(static_cast<float>((i - 125) * (i - 125) + (j - 125) * (j - 125)));

			convertToRGB(i, j);
			if (radius <= 125.0f)
				draw_to_color_pixels(250 - i, j, m_RGB[0], m_RGB[1], m_RGB[2]);
		}
	}
	refresh();
}

void HSLCircle::convertToRGB(int x, int y)
{
	float a = (1.0f - fabsf(2.0f * m_HSL[2] - 1.0f)) * m_S[x][y];
	float b = a * (1.0f - fabsf(fmodf(m_H[x][y] * 0.016666f, 2.0f) - 1.0f));
	float c = m_HSL[2] - a / 2.0f;

	m_RGB = {};

	if (m_H[x][y] < 60.0f) {
		m_RGB[0] = a + c;
		m_RGB[1] = b + c;
		m_RGB[2] = c;
	}
	else if (m_H[x][y] < 120.0f) {
		m_RGB[0] = b + c;
		m_RGB[1] = a + c;
		m_RGB[2] = c;
	}
	else if (m_H[x][y] < 180.0f) {
		m_RGB[0] = c;
		m_RGB[1] = a + c;
		m_RGB[2] = b + c;
	}
	else if (m_H[x][y] < 240.0f) {
		m_RGB[0] = c;
		m_RGB[1] = b + c;
		m_RGB[2] = a + c;
	}
	else if (m_H[x][y] < 300.0f) {
		m_RGB[0] = b + c;
		m_RGB[1] = c;
		m_RGB[2] = a + c;
	}
	else {
		m_RGB[0] = a + c;
		m_RGB[1] = c;
		m_RGB[2] = b + c;
	}

	m_RGB[0] *= 255.0f;
	m_RGB[1] *= 255.0f;
	m_RGB[2] *= 255.0f;
}
