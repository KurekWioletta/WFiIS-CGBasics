#include "RangeInput.h"

float RangeInput::m_selectedValue = 0.5;

RangeInput::RangeInput(float x, float y)
{
	// creating current value pointers
	m_linePointers[0] = new sf::VertexArray(sf::Lines, 2);
	m_linePointers[1] = new sf::VertexArray(sf::Lines, 2);
	(*m_linePointers[0])[0].color = (*m_linePointers[0])[1].color = sf::Color::Black;
	(*m_linePointers[1])[0].color = (*m_linePointers[1])[1].color = sf::Color::Black;

	// create grayscale gradient
	m_colorPixels = new sf::Uint8[m_inputSizeX * m_inputSizeY * 4];
	for (int i = 0; i < m_inputSizeX; i++) {
		for (int j = 0; j < m_inputSizeY; j++) {
			draw_to_color_pixels(i, j, j);
		}
	}
	//m_inputTexture = new sf::Texture();
	m_inputTexture.create(m_inputSizeX, m_inputSizeY);
	m_inputTexture.update(m_colorPixels);

	// create container
	m_rectangleInput = new sf::RectangleShape(sf::Vector2f(30, 255));
	m_rectangleInput->setTexture(&m_inputTexture);
	m_rectangleInput->setPosition(x, y);
	m_rectangleInput->setOutlineColor(sf::Color::Black);
	m_rectangleInput->setOutlineThickness(-1.0f);

	// add elements
	m_rangeInputElements.push_back(m_rectangleInput);
	m_rangeInputElements.push_back(m_linePointers[0]);
	m_rangeInputElements.push_back(m_linePointers[1]);

	// set pointer position
	m_xPos = x - 10;
	m_yPos = y;
	updatePosition(y + static_cast<int> (m_inputSizeY / 2));
}

RangeInput::~RangeInput()
{
	delete m_colorPixels;
	delete m_rectangleInput;
	delete m_linePointers[0];
	delete m_linePointers[1];
	m_rangeInputElements.clear();
}

void RangeInput::updatePosition(float y)
{
	(*m_linePointers[0])[0].position = sf::Vector2f(m_xPos, y);
	(*m_linePointers[0])[1].position = sf::Vector2f(m_xPos + 8, y);

	(*m_linePointers[1])[0].position = sf::Vector2f(m_xPos + m_inputSizeX + 12, y);
	(*m_linePointers[1])[1].position = sf::Vector2f(m_xPos + m_inputSizeX + 20, y);

	m_selectedValue = (y - m_yPos)/255.0f; 
}

float RangeInput::getSelectedValue()
{
	return m_selectedValue;
}

std::vector<sf::Drawable*> RangeInput::getElements()
{
	return m_rangeInputElements;
}
