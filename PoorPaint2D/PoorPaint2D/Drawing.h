#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp> 

class Drawing
{
public:
	Drawing(float x, float y);
	~Drawing();
	void refresh();
	sf::Sprite getDrawing(float x, float y);
	void setShapeBeginPoint(float x, float y);
	void setShapeEndPoint(float x, float y);
	void createCircle(sf::Color& color);
	void createLine(sf::Color& fgColor, sf::Color bgColor = sf::Color::Transparent);
	void createRectangle(sf::Color& fgColor, sf::Color bgColor = sf::Color::Transparent);
	void updateLine();
	void updateRectangle();
	void updateCircle();
	void finishShape();
	void loadFromFile();
	void saveToFile();
	void clearDrawing();
private:
	const unsigned int RENDER_SIZE_X = 700;
	const unsigned int RENDER_SIZE_Y = 600;

	sf::Vector2f m_shapeBeginPoint;
	sf::Vector2f m_shapeEndPoint;
	sf::RenderTexture m_renderTexture;
	sf::Texture m_texture;
	sf::Drawable* m_shape = nullptr;
	std::vector<sf::Drawable*> m_savedShapes;
};

