#pragma once
#include "Circle.h"

class RGBCircle : public Circle
{
public:
	RGBCircle(float x, float y);
private:
	void updateTexture() override;
};