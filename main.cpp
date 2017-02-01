#include "fregger.h"
#include "FrogGame.h"
#include <SFML/Graphics.hpp>

int WinMain() {
	
	loadText();
	loadTextures();
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "go to the top", sf::Style::Close);
	

	game g(0, &window);
	
}