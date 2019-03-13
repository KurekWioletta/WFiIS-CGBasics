#include "Menu.h"
#include "font.h" 
 
Menu::Menu() : m_colorForeground(sf::Color::White), m_colorBackground(sf::Color::Green)
{   
	m_font.loadFromMemory(font_data, font_data_size);
	m_text = new sf::Text;
	m_text->setFont(m_font);
	m_text->setCharacterSize(12);
	m_text->setFillColor(sf::Color::White);

	m_rectangle = new sf::RectangleShape(sf::Vector2f(796, 536));
	m_rectangle->setFillColor(sf::Color::Transparent);
	m_rectangle->setOutlineColor(sf::Color::White);
	m_rectangle->setOutlineThickness(1.0f);
	m_rectangle->setPosition(2, 62);

	m_rectangleForegroundColor = new sf::RectangleShape(sf::Vector2f(32, 30));
	m_rectangleForegroundColor->setFillColor(m_colorForeground);
	m_rectangleForegroundColor->setOutlineColor(m_colorForeground);
	m_rectangleForegroundColor->setPosition(767, 1);

	m_rectangleBackgroundColor = new sf::RectangleShape(sf::Vector2f(32, 30));
	m_rectangleBackgroundColor->setFillColor(m_colorBackground);
	m_rectangleBackgroundColor->setOutlineColor(m_colorBackground);
	m_rectangleBackgroundColor->setPosition(767, 31);

	unsigned int x, y;
	m_colorsPixels = new sf::Uint8[COLORS_SIZE_X * COLORS_SIZE_Y * 4];
	for (x = 0; x < 255; x++)
		for (y = 0; y < 30; y++)
		{
			draw_to_color_pixels(x, y, x, 255, 0);
			draw_to_color_pixels(x + 255, y, 255, 255 - x, 0);
			draw_to_color_pixels(x + 510, y, 255, 0, x);
			draw_to_color_pixels(254 - x, y + 30, 0, 255, 255 - x);
			draw_to_color_pixels(509 - x, y + 30, 0, x, 255);
			draw_to_color_pixels(764 - x, y + 30, 255 - x, 0, 255);
		}

	m_colorsTexture = new sf::Texture();
	m_colorsTexture->create(COLORS_SIZE_X, COLORS_SIZE_Y);
	m_colorsTexture->update(m_colorsPixels);

	m_colorSprite = new sf::Sprite();
	m_colorSprite->setTexture(*m_colorsTexture);
	m_colorSprite->setPosition(1, 1);
}

Menu::~Menu() 
{
	delete m_text;
	delete m_rectangle;
	delete m_rectangleBackgroundColor;
	delete m_rectangleForegroundColor;
	delete m_colorsPixels;
	delete m_colorSprite;
	delete m_colorsTexture;
}

void Menu::setForegroundColor(unsigned int x, unsigned int y)
{
	if (x < COLORS_SIZE_X && y < COLORS_SIZE_Y && x >= 0 && y >= 0) {
		m_colorForeground 
			= sf::Color(m_colorsPixels[4 * (y * COLORS_SIZE_X + x) + 0],
						m_colorsPixels[4 * (y * COLORS_SIZE_X + x) + 1], 
						m_colorsPixels[4 * (y * COLORS_SIZE_X + x) + 2], 
						255);

		m_rectangleForegroundColor->setFillColor(m_colorForeground);
		m_rectangleForegroundColor->setOutlineColor(m_colorForeground);
	}
}

void Menu::setBackgroundColor(unsigned int x, unsigned int y)
{
	if (x < COLORS_SIZE_X && y < COLORS_SIZE_Y && x >= 0 && y >= 0) {
		m_colorBackground
			= sf::Color(m_colorsPixels[4 * (y * COLORS_SIZE_X + x) + 0],
				m_colorsPixels[4 * (y * COLORS_SIZE_X + x) + 1],
				m_colorsPixels[4 * (y * COLORS_SIZE_X + x) + 2],
				255);

		m_rectangleBackgroundColor->setFillColor(m_colorBackground);
		m_rectangleBackgroundColor->setOutlineColor(m_colorBackground);
	}
}

void Menu::setCurrentMode(char mode)
{
	m_currentMode = mode;
}

sf::Color& Menu::getForegroundColor()
{
	return m_colorForeground;
}

sf::Color& Menu::getBackgroundColor()
{
	return m_colorBackground;
}

void Menu::outtextxy(sf::RenderTarget& target, float x, float y, const wchar_t *str) const
{
	m_text->setPosition(x, y);
	m_text->setString(str);
	target.draw(*m_text);
}

void Menu::outtextxy(sf::RenderTarget& target, float x, float y, wchar_t str) const
{
	m_text->setPosition(x, y);
	m_text->setString(str);
	target.draw(*m_text);
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	outtextxy(target, 5, 600, L"f - wybór koloru rysowania");
	outtextxy(target, 5, 615, L"b - wybór koloru wypelniania");
	outtextxy(target, 5, 630, L"l - rysowanie linii");

	outtextxy(target, 200, 600, L"r - rysowanie prostokata");
	outtextxy(target, 200, 615, L"a - rysowanie wypelnionego prostokata");
	outtextxy(target, 200, 630, L"c - rysowanie okregu");

	outtextxy(target, 470, 600, L"w - zapis do pliku");
	outtextxy(target, 470, 615, L"o - odczyt z pliku");
	outtextxy(target, 470, 630, L"esc - wyjscie");

	outtextxy(target, 650, 615, L"Aktualne: ");
	outtextxy(target, 710, 615, static_cast<wchar_t>(m_currentMode));

	target.draw(*m_rectangle);
	target.draw(*m_rectangleForegroundColor);
	target.draw(*m_rectangleBackgroundColor);
	target.draw(*m_colorSprite);
}