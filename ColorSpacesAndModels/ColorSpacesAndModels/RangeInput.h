#pragma once
#include <SFML/Graphics.hpp> 
#include <array>
#include <vector>

class RangeInput
{
public:
	RangeInput() = default;
	RangeInput(float x, float y);
	~RangeInput();
	void updatePosition(float y);
	static float getSelectedValue();
	std::vector<sf::Drawable*> getElements();
private:
	inline void draw_to_color_pixels(unsigned int x, unsigned int y, unsigned int z)
	{
		m_colorPixels[4 * (y * 30 + x) + 0] = z;
		m_colorPixels[4 * (y * 30 + x) + 1] = z;
		m_colorPixels[4 * (y * 30 + x) + 2] = z;
		m_colorPixels[4 * (y * 30 + x) + 3] = 255;
	}

	sf::RectangleShape* m_rectangleInput;
	std::array<sf::VertexArray*, 2> m_linePointers{};
	std::vector<sf::Drawable*> m_rangeInputElements;

	sf::Uint8* m_colorPixels;
	sf::Texture* m_inputTexture;

	int const m_inputSizeX = 30;
	int const m_inputSizeY = 255;
	float m_xPos;
	float m_yPos;

	static float m_selectedValue;
};

