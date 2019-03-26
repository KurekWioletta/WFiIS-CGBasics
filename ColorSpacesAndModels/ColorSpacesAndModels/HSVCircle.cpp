#include "HSVCircle.h"

HSVCircle::HSVCircle(float x, float y) : Circle(x, y)
{
	float radius, angle;
	for (int i = -125; i < 125; i++) {
		for (int j = -125; j < 125; j++) {
			radius = sqrt(static_cast<float>(i * i + j * j));
			angle = fmodf(atan2f(static_cast<float>(j), static_cast<float>(i)) * 180.0f / static_cast<float>(3.141592) + 180.0f, 360.0f);

			m_HSV[0] = angle / 360.f;
			m_HSV[1] = m_S[i + 125][j + 125] = (radius * 0.008f);
			m_HSV[2] = RangeInput::getSelectedValue();

			convertToRGB(i + 125, j + 125);

			if (radius <= 125.0f)
				draw_to_color_pixels(125 - i, 125 + j, m_RGB[0], m_RGB[1], m_RGB[2]);
		}
	}
	refresh();
}

void HSVCircle::updateTexture()
{
	float radius;
	m_HSV[2] = RangeInput::getSelectedValue();
	for (unsigned i = 0; i < 250; i++) {
		for (unsigned j = 0; j < 250; j++) {
			radius = sqrt(static_cast<float>((i - 125) * (i - 125) + (j - 125) * (j - 125)));
			updateRGB(i, j);

			if (radius <= 125.0f)
				draw_to_color_pixels(250 - i, j, m_RGB[0], m_RGB[1], m_RGB[2]);
		}
	}
	refresh();
}

void HSVCircle::convertToRGB(int x, int y)
{
	float region;
	int i;

	if (m_HSV[1] <= 0) {
		m_RGB = { m_HSV[2] * 255.0f, m_HSV[2] * 255.0f, m_HSV[2] * 255.0f };
		return;
	}
	
	region = m_HSV[0] * 6.0f; 
	if (region == 6.0f) 
		region = 0.0f;

	m_i[x][y] = i = static_cast<int>(region);

	m_p[x][y] = 1.0f - m_HSV[1];
	m_q[x][y] = 1.0f - m_HSV[1] * (region - i);
	m_t[x][y] = 1.0f - m_HSV[1] * (1.0f - (region - i));
	
	updateRGB(x, y);
}

void HSVCircle::updateRGB(int x, int y)
{
	if (m_S[x][y] <= 0) {
		m_RGB = { m_HSV[2] * 255.0f, m_HSV[2] * 255.0f, m_HSV[2] * 255.0f };
		return;
	}

	switch (m_i[x][y]) {
	case 0:
		m_RGB[0] = m_HSV[2]; // R = V
		m_RGB[1] = m_HSV[2] * m_t[x][y]; // G = t
		m_RGB[2] = m_HSV[2] * m_p[x][y]; // B = p
		break;
	case 1:
		m_RGB[0] = m_HSV[2] * m_q[x][y]; // R = q
		m_RGB[1] = m_HSV[2]; // G = V
		m_RGB[2] = m_HSV[2] * m_p[x][y]; // B = p
		break;
	case 2:
		m_RGB[0] = m_HSV[2] * m_p[x][y]; // R = p
		m_RGB[1] = m_HSV[2]; // G = V
		m_RGB[2] = m_HSV[2] * m_t[x][y]; // B = t
		break;
	case 3:
		m_RGB[0] = m_HSV[2] * m_p[x][y]; // R = p
		m_RGB[1] = m_HSV[2] * m_q[x][y]; // G = q
		m_RGB[2] = m_HSV[2]; // B = V
		break;
	case 4:
		m_RGB[0] = m_HSV[2] * m_t[x][y]; // R = t
		m_RGB[1] = m_HSV[2] * m_p[x][y]; // G = p
		m_RGB[2] = m_HSV[2]; // B = V
		break;
	default:
		m_RGB[0] = m_HSV[2]; // R = V
		m_RGB[1] = m_HSV[2] * m_p[x][y]; // G = p
		m_RGB[2] = m_HSV[2] * m_q[x][y]; // B = q
		break;
	}

	m_RGB[0] *= 255.0f;
	m_RGB[1] *= 255.0f;
	m_RGB[2] *= 255.0f;
}
