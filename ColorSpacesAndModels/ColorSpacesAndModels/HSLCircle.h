#pragma once
#include "Circle.h"
#include <array>

class HSLCircle : public Circle
{
public:
	HSLCircle(float x, float y);
	void updateTexture() override;
private:
	void convertToRGB(int x, int y);
	std::array<float, 3> m_HSL;
	std::array<float, 3> m_RGB;
	float m_H[250][250];
	float m_S[250][250];
}; 

