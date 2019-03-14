#include "Drawing.h"

Drawing::Drawing(float x, float y)
{
	m_renderTexture.create(x, y);
	m_renderTexture.clear(sf::Color::Black);
}

Drawing::~Drawing()
{
	for (sf::Drawable* shape : m_savedShapes)
		delete shape;
	m_savedShapes.clear();
}

void Drawing::refresh() 
{
	m_renderTexture.clear(sf::Color::Black);

	m_renderTexture.draw(sf::Sprite(m_texture));
	
	// draw previous shapes
	for (sf::Drawable* shape: m_savedShapes)
		m_renderTexture.draw(*shape);

	// draw new shape
	if (m_shape != nullptr)
		m_renderTexture.draw(*m_shape);

	m_renderTexture.display();
}

sf::Sprite Drawing::getDrawing(float x, float y)
{
	sf::Sprite sprite(m_renderTexture.getTexture());
	sprite.setPosition(x, y);
	return sprite;
}

void Drawing::setShapeBeginPoint(float x, float y)
{
	m_shapeBeginPoint = sf::Vector2f(x, y);
}

void Drawing::setShapeEndPoint(float x, float y)
{
	m_shapeEndPoint = sf::Vector2f(x, y);
}

void Drawing::createLine(sf::Color& fgColor, sf::Color bgColor)
{
	sf::VertexArray* line = new sf::VertexArray(sf::LinesStrip, 2);
	(*line)[0].position = m_shapeBeginPoint;
	(*line)[1].position = m_shapeBeginPoint;
	
	(*line)[0].color = fgColor;
	(*line)[1].color = bgColor;

	m_shape = line;
} 

void Drawing::createRectangle(sf::Color& fgColor, sf::Color bgColor)
{
	sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2f(1, 1));
	rectangle->setPosition(m_shapeBeginPoint);

	rectangle->setFillColor(bgColor);
	rectangle->setOutlineColor(fgColor);
	rectangle->setOutlineThickness(-1.0f);

	m_shape = rectangle;
}

void Drawing::createCircle(sf::Color& color)
{
	sf::CircleShape* circle = new sf::CircleShape(1);
	circle->setPosition(m_shapeBeginPoint.x - 1, m_shapeBeginPoint.y - 1);
	circle->setRotation(atan2f(0, 0));

	circle->setOutlineThickness(1.0f);
	circle->setOutlineColor(color);
	circle->setFillColor(sf::Color::Transparent);

	m_shape = circle;
}

void Drawing::updateLine() 
{
	sf::VertexArray* line = dynamic_cast<sf::VertexArray*>(m_shape);
	(*line)[1].position = m_shapeEndPoint;
}

void Drawing::updateRectangle()
{
	sf::RectangleShape* rectangle = dynamic_cast<sf::RectangleShape*>(m_shape);

	float scaleX = 1.0;
	float scaleY = 1.0;

	if (rectangle->getPosition().x > m_shapeEndPoint.x)
		scaleX *= -1;
	if (rectangle->getPosition().y > m_shapeEndPoint.y)
		scaleY *= -1;

	sf::Vector2f size;

	size.x = abs(rectangle->getPosition().x - m_shapeEndPoint.x);
	size.y = abs(rectangle->getPosition().y - m_shapeEndPoint.y);

	rectangle->setScale(scaleX, scaleY);
	rectangle->setSize(size);
}

void Drawing::updateCircle()
{
	sf::CircleShape* circle = dynamic_cast<sf::CircleShape*>(m_shape);

	float radius = sqrt(pow(m_shapeEndPoint.x - m_shapeBeginPoint.x, 2) + pow(m_shapeEndPoint.y - m_shapeBeginPoint.y, 2)) / 2;
	float angle = atan2f(m_shapeEndPoint.x - m_shapeBeginPoint.x, m_shapeEndPoint.y - m_shapeBeginPoint.y);
	
	float scaleX = 1.0;
	float scaleY = 1.0;

	if (circle->getPosition().x > m_shapeEndPoint.x) 
		scaleX *= -1;
	if (circle->getPosition().y > m_shapeEndPoint.y)
		scaleY *= -1;

	circle->setRotation(angle);
	circle->setRadius(radius);
	circle->setScale(scaleX, scaleY);
}

void Drawing::finishShape()
{
	m_savedShapes.push_back(m_shape);
}

void Drawing::loadFromFile()
{
	clearDrawing();
	m_texture.loadFromFile("example.png"); 
	m_texture.setSmooth(true);
}

void Drawing::saveToFile()
{
	m_renderTexture.getTexture().copyToImage().saveToFile("example.png");
}

void Drawing::clearDrawing()
{
	for (int i = 0; i < m_savedShapes.size(); i++)
		m_savedShapes.pop_back();
	m_savedShapes.clear();
	m_shape = nullptr;
}
