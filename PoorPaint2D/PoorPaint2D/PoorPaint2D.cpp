#include "Menu.h"
#include "Window.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp> 

int main()
{
	Window* window = new Window();

	while (window->getRenderWindow().isOpen())
	{
		window->refresh();
	}

	delete window;

	return 0;
}