#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp> 
#include "Circle.h"
#include "RGBCircle.h"
#include "CMYCircle.h"
#include "HSLCircle.h"
#include "HSVCircle.h"
#include "Text.h"
#include "RangeInput.h"

class Window
{
public:
	Window();
	~Window();
	bool isOpen() const;
	void refresh();
	void clear();
	void drawElements();
	void handleEvents(); 
	void showFps();
private:
	sf::RenderWindow m_renderWindow;
	sf::RenderTexture m_renderTexture;
	sf::Time m_time = sf::Time::Zero;
	sf::Event m_event;
	sf::Clock m_clock;

	std::vector<Circle*> m_circles;
	RangeInput* m_rangeInput;
	Text m_text;

	bool m_mousePressed = false;
	int m_frameCounter = 0;
	unsigned int m_fps = 0;
};

