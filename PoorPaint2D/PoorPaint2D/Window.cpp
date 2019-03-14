#include "Window.h"

Window::Window() : m_renderWindow(sf::VideoMode(800, 650), "PoorPaint2D", sf::Style::Titlebar | sf::Style::Close)
{
	m_renderWindow.setFramerateLimit(60);  
	m_drawing = new Drawing(m_drawingAreaPosition[2] - m_drawingAreaPosition[0], m_drawingAreaPosition[3] - m_drawingAreaPosition[1]);
}

Window::~Window()
{
	delete m_drawing;
}

void Window::refresh()
{
	m_renderWindow.clear(sf::Color::Black);
	while (m_renderWindow.pollEvent(m_event))
	{
		handleEvents();
	} 
	m_drawing->refresh();
	m_renderWindow.draw(m_menu);
	m_renderWindow.draw(m_drawing->getDrawing(m_drawingAreaPosition[0], m_drawingAreaPosition[1]));
	m_renderWindow.display();
}

void Window::handleEvents()
{
	switch (m_event.type)
	{
	case sf::Event::Closed:
		m_renderWindow.close();
		break;

	case sf::Event::MouseMoved:
		updateDrawing();
		break;

	case sf::Event::MouseButtonPressed:
		onMouseButtonPressed();
		break;

	case sf::Event::MouseButtonReleased:
		finishDrawing();
		break;

	case sf::Event::KeyPressed:
		onKeyPressed();
		break;
	}
}

void Window::onKeyPressed()
{
	m_selectedAppOption = m_event.key.code;

	switch (m_event.key.code)
	{
	case sf::Keyboard::Escape:
		m_renderWindow.close();
		break;
	case sf::Keyboard::O:
		m_drawing->loadFromFile();
		m_menu.setCurrentMode('o');
		break;
	case sf::Keyboard::W:
		m_drawing->saveToFile();
		m_menu.setCurrentMode('w');
		break;
	case sf::Keyboard::F:
		m_menu.setCurrentMode('f');
		break;
	case sf::Keyboard::B:
		m_menu.setCurrentMode('b');
		break;
	case sf::Keyboard::L:
		m_menu.setCurrentMode('l');
		break;
	case sf::Keyboard::R:
		m_menu.setCurrentMode('r');
		break;
	case sf::Keyboard::A:
		m_menu.setCurrentMode('a');
		break;
	case sf::Keyboard::C:
		m_menu.setCurrentMode('c');
		break;
	}
}

void Window::onMouseButtonPressed()
{
	if (m_selectedAppOption == AppOptions::SelectForegroundColor)
		m_menu.setForegroundColor(m_event.mouseButton.x, m_event.mouseButton.y);
	else if (m_selectedAppOption == AppOptions::SelectBackgroundColor)
		m_menu.setBackgroundColor(m_event.mouseButton.x, m_event.mouseButton.y);
	else 
		startDrawing();
}

void Window::startDrawing()
{
	if (isOutOfBounds(m_event.mouseButton.x, m_event.mouseButton.y))
		return;

	float x = m_event.mouseButton.x - m_drawingAreaPosition[0]; // fixing position to fit drawing area
	float y = m_event.mouseButton.y - m_drawingAreaPosition[1];

	m_drawing->setShapeBeginPoint(x, y);

	m_startedDrawing = true;

	switch (m_selectedAppOption)
	{
	case AppOptions::DrawLine:
		m_drawing->createLine(m_menu.getForegroundColor(), m_menu.getBackgroundColor());
		break;
	case AppOptions::DrawRectangle:
		m_drawing->createRectangle(m_menu.getForegroundColor());
		break;
	case AppOptions::DrawFilledRectangle:
		m_drawing->createRectangle(m_menu.getForegroundColor(), m_menu.getBackgroundColor());
		break;
	case AppOptions::DrawCircle:
		m_drawing->createCircle(m_menu.getForegroundColor());
		break;
	default:
		m_startedDrawing = false;
		break;
	}
}

void Window::updateDrawing()
{
	if (isOutOfBounds(m_event.mouseMove.x, m_event.mouseMove.y) || !m_startedDrawing)
		return;

	float x = m_event.mouseMove.x - m_drawingAreaPosition[0]; // fixing position to fit drawing area
	float y = m_event.mouseMove.y - m_drawingAreaPosition[1];

	m_drawing->setShapeEndPoint(x, y);
	
	switch (m_selectedAppOption)
	{
	case AppOptions::DrawLine:
		m_drawing->updateLine();
		break;
	case AppOptions::DrawFilledRectangle:
	case AppOptions::DrawRectangle:
		m_drawing->updateRectangle();
		break;
	case AppOptions::DrawCircle:
		m_drawing->updateCircle();
		break;
	}
}

void Window::finishDrawing()
{
	if (!m_startedDrawing)
		return;

	m_startedDrawing = false;
	m_drawing->finishShape();
}

bool Window::isOutOfBounds(int x, int y)
{
	if (x < m_drawingAreaPosition[0] || y < m_drawingAreaPosition[1] || x > m_drawingAreaPosition[2] ||y > m_drawingAreaPosition[3]) 
		return true;

	return false;
}