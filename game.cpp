#include "game.h"
#include <vector>
#include <SFML/Graphics.hpp>


const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 10;

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

cell::cell(int _ground, sf::Vector2i _boardPos, sf::Vector2f _pixelPos) {
	ground = _ground;
	boardPos = _boardPos;
	pixelPos = _pixelPos;

}

void board::init(ByteVec& boardMap) {
	bg.create(WINDOW_WIDTH, WINDOW_HEIGHT);
	std::vector<cell> currentRow;
	int xImagePositionFactor = WINDOW_WIDTH / BOARD_WIDTH;
	int yImagePositionFactor = WINDOW_HEIGHT / BOARD_HEIGHT;
	sf::Vector2f cellSpriteScale((float)WINDOW_WIDTH / ((float)BOARD_WIDTH * (float)TEXTURE_DIRT.getSize().x),
								(float)WINDOW_HEIGHT / ((float)BOARD_HEIGHT * (float)TEXTURE_DIRT.getSize().y));
	


	for (int y = 0; y < BOARD_HEIGHT; y++) {
		currentRow.clear();
		for (int x = 0; x < BOARD_WIDTH; x++) {
			sf::Vector2i boardLoc(x, y);
			cell tmpCell = cell(boardMap[y*BOARD_HEIGHT + x], boardLoc , getPixelCoords(boardLoc));
			sf::Sprite sprite;
			sprite.setTexture(tmpCell.getTexture());
			sprite.setPosition(tmpCell.pixelPos);
			sprite.scale(cellSpriteScale);

			bg.draw(sprite);
			currentRow.push_back(tmpCell);
		}
		gameBoard.push_back(currentRow);
	}
	bg.display();
	background.setTexture(bg.getTexture());
}

board::board() {
	init(defaultMap);
}

sf::Texture& cell::getTexture() {
	switch (ground) {
	case DIRT:
		return(TEXTURE_DIRT);
	case WATER:
		return(TEXTURE_WATER);
	default:
		throw new std::out_of_range("Texture not found");
	}
}

sf::Vector2f getPixelCoords(int x, int y) {
	float xBoardWindowRatio = (float)WINDOW_WIDTH / (float)BOARD_WIDTH;
	float yBoardWindowRatio = (float)WINDOW_HEIGHT / (float)BOARD_HEIGHT;
	sf::Vector2f tmp;
	tmp.x = x * xBoardWindowRatio;
	tmp.y = y * yBoardWindowRatio;
	return(tmp);
}

sf::Vector2f getPixelCoords(sf::Vector2i v) {
	return(getPixelCoords(v.x, v.y));
}

sf::Vector2i getBoardCoords(int x, int y) {
	float xBoardWindowRatio = (float)BOARD_WIDTH / (float)WINDOW_WIDTH;
	float yBoardWindowRatio = (float)BOARD_HEIGHT / (float)WINDOW_HEIGHT;
	sf::Vector2i tmp;
	tmp.x = std::lrintf(x * xBoardWindowRatio);
	tmp.y = std::lrintf(y * yBoardWindowRatio);
	return(tmp);
}

sf::Vector2i getBoardCoords(sf::Vector2f v) {
	return(getBoardCoords(v.x, v.y));
}

