#pragma once
#include <SFML/Graphics.hpp> 
#include "RangeInput.h"

class Circle
{
public:
	Circle() = default;
	Circle(float x, float y);
	~Circle();
	void refresh();
	sf::CircleShape& getCircle() const;
	virtual void updateTexture();
protected:
	inline void draw_to_color_pixels(unsigned int x, unsigned int y, float r, float g, float b)
	{
		m_colorPixels[4 * (y * 250 + x) + 0] = static_cast<sf::Uint8>(r);
		m_colorPixels[4 * (y * 250 + x) + 1] = static_cast<sf::Uint8>(g);
		m_colorPixels[4 * (y * 250 + x) + 2] = static_cast<sf::Uint8>(b);
		m_colorPixels[4 * (y * 250 + x) + 3] = static_cast<sf::Uint8>(255);
	}

	sf::CircleShape* m_circle;
	sf::Uint8* m_colorPixels;
	sf::Texture m_texture;
};
