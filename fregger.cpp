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

sf::Text CRUSHED_TEXT;
sf::Text DROWNED_TEXT;
sf::Text WON_TEXT;
sf::Text OOB_TEXT;

sf::Font FONT;

void loadTextures() {
	TEXTURE_DIRT.loadFromFile("images/dirt.png");
	TEXTURE_WATER.loadFromFile("images/water.png");
	TEXTURE_FREG.loadFromFile("images/freg.png");
	TEXTURE_PIXEL.loadFromFile("images/pixel.png");
	TEXTURE_START.loadFromFile("images/start.png");
	TEXTURE_FINISH.loadFromFile("images/finish.png");
}

sf::Text getText(std::string text) {
	sf::Text tmp(text, FONT);
	tmp.setPosition(10, (WINDOW_HEIGHT / 2.0) - 50);
	tmp.setCharacterSize(70);
	tmp.setFillColor(sf::Color::Red);
	return(tmp);
}
void loadText() {
	FONT.loadFromFile("Inconsolata-Regular.ttf");
	CRUSHED_TEXT = getText("crushed | press R");
	DROWNED_TEXT = getText("drowned | press R");
	WON_TEXT = getText("you won it | press R");
	OOB_TEXT = getText("stay in it | press R");
}
