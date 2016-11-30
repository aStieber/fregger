#include "game.h"
#include <SFML/Graphics.hpp>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;


int WinMain()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!", sf::Style::Close);
	loadTextures();
	board b;


	//window.close();
	while (window.isOpen()) //main loop
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			//if up
			//if down
		}

		window.clear();
		window.draw(b.background);
		window.display();
	}

	return 0;
}