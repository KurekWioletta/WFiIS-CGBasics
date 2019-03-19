#include "Window.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp> 
 
int main() 
{
	Window* window = new Window();

	while (window->isOpen())
	{
		window->refresh();
	}

	delete window;

	return 0;
}