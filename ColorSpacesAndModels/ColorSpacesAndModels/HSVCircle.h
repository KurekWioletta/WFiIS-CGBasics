#pragma once
#include "Circle.h"
#include <array>

class HSVCircle : public Circle
{
public:
	HSVCircle(float x, float y);
	void updateTexture() override;
private:
	void convertToRGB(int x, int y);
	void updateRGB(int x, int y);

	std::array<float, 3> m_HSV;
	std::array<float, 3> m_RGB;

	// conversion cache
	float m_p[250][250] = { 0 };
	float m_q[250][250] = { 0 };
	float m_t[250][250] = { 0 };
	float m_S[250][250] = { 0 };
	int m_i[250][250] = { 0 };
};

