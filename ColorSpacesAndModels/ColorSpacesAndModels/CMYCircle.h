#pragma once
#include "Circle.h"

class CMYCircle : public Circle
{
public:
	CMYCircle(float x, float y);
private:
	void updateTexture() override;
};
