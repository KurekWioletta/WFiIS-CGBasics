#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp> 
#include <string>
#include "RangeInput.h"

class Text : public sf::Drawable {
public:
	Text();
	~Text();
	void updateFps(int fpsCounter);
	void setComponentValues();
	void outtextxy(sf::RenderTarget& target, float x, float y, std::string str) const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	sf::Font m_font;
	sf::Text *m_text;
	float m_lValue;
	float m_vValue;
	int m_yValue;
	int m_bValue;
	int m_fps = 0;
};

