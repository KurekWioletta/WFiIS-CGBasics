#include "Text.h"
#include "font.h"

Text::Text() : m_lValue(0), m_vValue(0), m_yValue(0), m_bValue(0)
{
	m_font.loadFromMemory(font_data, font_data_size);
	m_text = new sf::Text;
	m_text->setFont(m_font);
	m_text->setCharacterSize(13);
	m_text->setFillColor(sf::Color::Black);
}

Text::~Text()
{
	delete m_text;
}

void Text::updateFps(int fps)
{
	m_fps = fps;
}

void Text::setComponentValues()
{
	m_lValue = RangeInput::getSelectedValue();
	m_vValue = RangeInput::getSelectedValue();
	m_yValue = RangeInput::getSelectedValue() * 100;
	m_bValue = RangeInput::getSelectedValue() * 250.0f;
}

void Text::outtextxy(sf::RenderTarget & target, float x, float y, std::string str) const
{
	m_text->setPosition(x, y);
	m_text->setString(str);
	target.draw(*m_text); 
}

void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	outtextxy(target, 30, 30, "HSL");
	outtextxy(target, 315, 30, "HSV");
	outtextxy(target, 30, 315, "CMY");
	outtextxy(target, 315, 315, "RGB");

	outtextxy(target, 220, 270, "L=" + std::to_string(m_lValue));
	outtextxy(target, 510, 270, "V=" + std::to_string(m_vValue));
	outtextxy(target, 220, 550, "Y=" + std::to_string(m_yValue) + "%");
	outtextxy(target, 510, 550, "B=" + std::to_string(m_bValue));
	outtextxy(target, 647, 300, std::to_string(m_fps) + " FPS");
}