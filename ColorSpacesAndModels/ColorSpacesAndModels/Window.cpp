#include "Window.h"

Window::Window() 
	: m_renderWindow(sf::VideoMode(750, 595), "ColorSpacesAndModels", sf::Style::Titlebar | sf::Style::Close)
{
	//m_renderWindow.setFramerateLimit(60);
	m_renderTexture.create(750, 595);

	m_circles.push_back(new HSLCircle(30, 30));
	m_circles.push_back(new HSVCircle(315, 30));
	m_circles.push_back(new CMYCircle(30, 315));
	m_circles.push_back(new RGBCircle(315, 315));

	m_rangeInput = new RangeInput(650, 30);

	m_text.setComponentValues();
}

Window::~Window()
{
	delete m_rangeInput;
	for (auto circle : m_circles)
		delete circle;
	m_circles.clear();
}

bool Window::isOpen() const
{
	return m_renderWindow.isOpen();
}

void Window::refresh()
{
	clear();
	while (m_renderWindow.pollEvent(m_event))
	{
		handleEvents();
	}
	drawElements();
	showFps();
	m_renderWindow.display(); 
}

void Window::clear()
{
	m_renderTexture.clear(sf::Color::White);
	m_renderWindow.clear(sf::Color::White);
}

void Window::drawElements()
{
	// draw circles
	for (Circle* circle : m_circles)
		m_renderTexture.draw(circle->getCircle());

	// draw range input
	for (sf::Drawable* shape : m_rangeInput->getElements())
		m_renderTexture.draw(*shape);

	m_renderTexture.display();

	sf::Sprite sprite(m_renderTexture.getTexture());
	sprite.setPosition(0, 0);
	m_renderWindow.draw(sprite);

	m_renderWindow.draw(m_text);
}

void Window::handleEvents()
{
	switch (m_event.type)
	{
	case sf::Event::Closed:
		m_renderWindow.close();
		break;

	case sf::Event::MouseMoved:
		if (m_mousePressed && m_event.mouseMove.x >= 650 && m_event.mouseMove.x <= 680 && m_event.mouseMove.y >= 30 && m_event.mouseMove.y <= 285) {
			m_rangeInput->updatePosition(static_cast<float>(m_event.mouseMove.y));
			for (auto circle : m_circles)
				circle->updateTexture();
			m_text.setComponentValues();
		}
		break;

	case sf::Event::MouseButtonPressed:
		if (m_event.mouseButton.x >= 650 && m_event.mouseButton.x <= 680 && m_event.mouseButton.y >= 30 && m_event.mouseButton.y <= 285) {
			m_rangeInput->updatePosition(static_cast<float>(m_event.mouseButton.y));
			for (auto circle : m_circles)
				circle->updateTexture();
			m_text.setComponentValues();
			m_mousePressed = true;
		}
		break;

	case sf::Event::MouseButtonReleased:
		m_mousePressed = false;
		break;
	}
}

void Window::showFps()
{
	if (m_clock.getElapsedTime().asSeconds() >= 1.0f) {
		m_fps = static_cast<unsigned int>(static_cast<float>(m_frameCounter) / m_clock.getElapsedTime().asSeconds());
		m_clock.restart();
		m_frameCounter = 0;
	}
	m_frameCounter++;

	m_text.updateFps(m_fps);
}
