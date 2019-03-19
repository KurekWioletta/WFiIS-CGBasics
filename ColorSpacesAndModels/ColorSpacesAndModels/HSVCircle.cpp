#include "HSVCircle.h"

HSVCircle::HSVCircle(float x, float y) : Circle(x, y)
{
	float radius, angle;
	for (int i = -125; i < 125; i++) {
		for (int j = -125; j < 125; j++) {
			radius = sqrt(static_cast<float>(i * i + j * j));
			angle = fmodf(atan2f(static_cast<float>(j), static_cast<float>(i)) * 180.0f / static_cast<float>(3.141592) + 180.0f, 360.0f);

			m_HSV[0] = m_radiusArray[i + 125][j + 125] = angle / 360.f;
			m_HSV[1] = m_angleArray[i + 125][j + 125] = radius * 0.008f;
			m_HSV[2] = RangeInput::getSelectedValue();

			convertToRGB();

			if (radius <= 125.0f)
				draw_to_color_pixels(125 - i, 125 + j, m_RGB[0], m_RGB[1], m_RGB[2]);
		}
	}
	refresh();
}

void HSVCircle::updateTexture()
{
	for (unsigned i = 0; i < 250; i++) {
		for (unsigned j = 0; j < 250; j++)
		{
			m_HSV[0] = m_radiusArray[i][j];
			m_HSV[1] = m_angleArray[i][j];
			m_HSV[2] = RangeInput::getSelectedValue();

			convertToRGB();
			draw_to_color_pixels(i, j, m_RGB[0], m_RGB[1], m_RGB[2]);
		}
	}
	refresh();
}

void HSVCircle::convertToRGB()
{
	float region, remainder, p, q, t;
	int i;

	if (m_HSV[1] <= 0) {
		m_RGB = { m_HSV[2] * 255.0f, m_HSV[2] * 255.0f, m_HSV[2] * 255.0f };
		return;
	}
	
	region = m_HSV[0] * 6.0f; 
	if (region == 6.0f) 
		region = 0.0f;

	i = static_cast<int>(region);

	remainder = region - i;

	p = m_HSV[2] * (1.0f - m_HSV[1]);
	q = m_HSV[2] * (1.0f - m_HSV[1] * remainder);
	t = m_HSV[2] * (1.0f - m_HSV[1] * (1.0f - remainder));
	
	switch (i) {
	case 0:
		m_RGB[0] = m_HSV[2]; // R = V
		m_RGB[1] = t; // G = t
		m_RGB[2] = p; // B = p
		break;
	case 1:
		m_RGB[0] = q; // R = g
		m_RGB[1] = m_HSV[2]; // G = V
		m_RGB[2] = p; // B = p
		break;
	case 2:
		m_RGB[0] = p; // R = p
		m_RGB[1] = m_HSV[2]; // G = V
		m_RGB[2] = t; // B = t
		break;
	case 3:
		m_RGB[0] = p; // R = p
		m_RGB[1] = q; // G = q
		m_RGB[2] = m_HSV[2]; // B = V
		break;
	case 4:
		m_RGB[0] = t; // R = t
		m_RGB[1] = p; // G = p
		m_RGB[2] = m_HSV[2]; // B = V
		break;
	default:
		m_RGB[0] = m_HSV[2]; // R = V
		m_RGB[1] = p; // G = p
		m_RGB[2] = q; // B = q
		break;
	}

	m_RGB[0] *= 255.0f;
	m_RGB[1] *= 255.0f;
	m_RGB[2] *= 255.0f;
}
