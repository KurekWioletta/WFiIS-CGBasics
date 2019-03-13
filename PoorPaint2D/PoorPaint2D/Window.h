#pragma once
#include "Menu.h"
#include "Drawing.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp> 

enum AppOptions {
	SelectForegroundColor = sf::Keyboard::F,
	SelectBackgroundColor = sf::Keyboard::B,
	DrawLine = sf::Keyboard::L,
	DrawRectangle = sf::Keyboard::R,
	DrawFilledRectangle = sf::Keyboard::A,
	DrawCircle = sf::Keyboard::C
};

class Window
{
public:
	Window();
	~Window();
	sf::RenderWindow& getRenderWindow() { return m_renderWindow; }; 
	void refresh();
private:
	sf::Keyboard::Key m_selectedAppOption;
	sf::RenderWindow m_renderWindow;
	sf::Event m_event;

	Menu m_menu;
	Drawing *m_drawing;

	const float m_drawingAreaPosition[4] = { 2., 62., 798., 598.}; // {left, top, right, bottom} - right = left + width...
	bool m_startedDrawing = false;

	void handleEvents();
	void onKeyPressed();
	void onMouseButtonPressed();
	void startDrawing();
	void updateDrawing();
	void finishDrawing();
	bool isOutOfBounds(int x, int y);
};
 
