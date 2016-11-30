#include "game.h"
#include <vector>
#include <SFML/Graphics.hpp>


const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 10;

sf::Texture TEXTURE_DIRT;
sf::Texture TEXTURE_WATER;

const enum { DIRT, WATER, ROAD }; //ground types

ByteVec defaultMap = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
						1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
						1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
						1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
						1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
						0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

cell::cell(int _ground, int _xPos, int _yPos)
{
	ground = _ground;
	xPos = _xPos;
	yPos = _yPos;
}

void board::init(ByteVec& boardMap)
{
	bg.create(WINDOW_WIDTH, WINDOW_HEIGHT);
	std::vector<cell> currentRow;
	int xImagePositionFactor = WINDOW_WIDTH / BOARD_WIDTH;
	int yImagePositionFactor = WINDOW_HEIGHT / BOARD_HEIGHT;
	sf::Vector2f cellSpriteScale((float)TEXTURE_DIRT.getSize().x / 10 * ((float)BOARD_WIDTH / (float)WINDOW_WIDTH), (float)TEXTURE_DIRT.getSize().y / 10 * ((float)BOARD_HEIGHT / (float)WINDOW_HEIGHT));



	for (int y = 0; y < BOARD_HEIGHT; y++)
	{
		currentRow.clear();
		for (int x = 0; x < BOARD_WIDTH; x++)
		{
			cell tmpCell = cell(boardMap[y*BOARD_HEIGHT + x], x, y);
			sf::Sprite sprite;
			sprite.setTexture(tmpCell.getTexture());
			sprite.setPosition(x * xImagePositionFactor, y * yImagePositionFactor);
			sprite.scale(cellSpriteScale);
			bg.draw(sprite);
			currentRow.push_back(tmpCell);
		}
		gameBoard.push_back(currentRow);
	}
	bg.display();
	background.setTexture(bg.getTexture());
}

board::board()
{
	init(defaultMap);
}
 
board::board(ByteVec& map)
{
	if (map.size() == 100) { init(map); }
}


sf::Texture& cell::getTexture()
{
	switch (ground)
	{
	case DIRT:
		return(TEXTURE_DIRT);
	case WATER:
		return(TEXTURE_WATER);
	default:
		throw new std::out_of_range("Texture not found");
	}
}

void loadTextures()
{
	TEXTURE_DIRT.loadFromFile("images/dirt.png");
	TEXTURE_WATER.loadFromFile("images/water.png");
}