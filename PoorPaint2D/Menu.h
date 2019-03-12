#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp> 

class Menu : public sf::Drawable
{
public:
	Menu();
	~Menu();
	void setForegroundColor(unsigned int x, unsigned int y);
	void setBackgroundColor(unsigned int x, unsigned int y);
	void setCurrentMode(char mode);
	sf::Color& getForegroundColor();
	sf::Color& getBackgroundColor();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	const unsigned int COLORS_SIZE_X = 765;
	const unsigned int COLORS_SIZE_Y = 60;

	sf::Font m_font;
	sf::Text* m_text;
	sf::Color m_colorForeground;
	sf::Color m_colorBackground;

	sf::RectangleShape* m_rectangle;
	sf::RectangleShape* m_rectangleForegroundColor;
	sf::RectangleShape* m_rectangleBackgroundColor;

	sf::Texture* m_colorsTexture;
	sf::Sprite* m_colorSprite;
	sf::Uint8* m_colorsPixels;

	char m_currentMode = ' ';

	inline void draw_to_color_pixels(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b)
	{
		m_colorsPixels[4 * (y * COLORS_SIZE_X + x) + 0] = r;
		m_colorsPixels[4 * (y * COLORS_SIZE_X + x) + 1] = g;
		m_colorsPixels[4 * (y * COLORS_SIZE_X + x) + 2] = b;
		m_colorsPixels[4 * (y * COLORS_SIZE_X + x) + 3] = 255;
	}

	void outtextxy(sf::RenderTarget& target, float x, float y, const wchar_t *str) const;
	void outtextxy(sf::RenderTarget& target, float x, float y, wchar_t str) const;

};