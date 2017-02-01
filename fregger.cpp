#include "fregger.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int NUM_METERS_PER_CELL = 1;

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 10;

sf::Texture TEXTURE_DIRT;
sf::Texture TEXTURE_WATER;
sf::Texture TEXTURE_FREG;
sf::Texture TEXTURE_PIXEL;
sf::Texture TEXTURE_START;
sf::Texture TEXTURE_FINISH;

sf::Text crushedText;
sf::Text drownedText;
sf::Text wonText;
sf::Text oobText;

void loadTextures() {
	TEXTURE_DIRT.loadFromFile("images/dirt.png");
	TEXTURE_WATER.loadFromFile("images/water.png");
	TEXTURE_FREG.loadFromFile("images/freg.png");
	TEXTURE_PIXEL.loadFromFile("images/pixel.png");
	TEXTURE_START.loadFromFile("images/start.png");
	TEXTURE_FINISH.loadFromFile("images/finish.png");
}

sf::Text getText(std::string text, sf::Font& font) {
	sf::Text tmp(text, font);
	tmp.setPosition(10, (WINDOW_HEIGHT / 2.0) - 50);
	tmp.setCharacterSize(70);
	tmp.setFillColor(sf::Color::Red);
	return(tmp);
}
void loadText() {
	sf::Font font;
	font.loadFromFile("Inconsolata-Regular.ttf");
	crushedText = getText("crushed | press R", font);
	drownedText = getText("drowned | press R", font);
	wonText = getText("you won it | press R", font);
	oobText = getText("stay in it | press R", font);
}
