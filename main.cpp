#include "fregger.h"
#include "FrogGame.h"

#include <SFML/Graphics.hpp>
#include <iostream>

//int WinMain() { //project properties -> Linker -> SUBSYSTEM to WINDOWS to remove console. Then uncomment this. 
int main() {
	//init
	loadText();
	loadTextures();
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "go to the top", sf::Style::Close);
	//end init
	bool neuralNetMode = false;

	if (neuralNetMode) {

	}
	else {
		game g(neuralNetMode, &window);
	}
	
	

	
	
}