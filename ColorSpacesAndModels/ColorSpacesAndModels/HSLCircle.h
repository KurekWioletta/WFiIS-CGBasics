#pragma once
#include "Circle.h"
#include <array>

class HSLCircle : public Circle
{
public:
	HSLCircle(float x, float y);
	void updateTexture() override;
private:
	std::array<float, 3> m_HSL;
	std::array<float, 3> m_RGB;
	float m_radiusArray[250][250];
	float m_angleArray[250][250];
	void convertToRGB(); 
}; 

