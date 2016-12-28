#include "game.h"
#include <vector>
#include <SFML/Graphics.hpp>

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 10;


const enum { DIRT, WATER, ROAD, START, FINISH }; //ground types

ByteVec defaultMap = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
						1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
						1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
						1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
						1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
						0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 3, 0, 0, 0, 0, 0 };
/* ByteVec defaultMap = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
						1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
						1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
						1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
						1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
						0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
*/

cell::cell(int _ground, sf::Vector2i _boardPos, sf::Vector2f _meterPos) {
	ground = _ground;
	boardPos = _boardPos;
	meterPos = _meterPos;
}

void board::init(ByteVec& boardMap) {
	bg.create(WINDOW_WIDTH, WINDOW_HEIGHT);
	std::vector<cell> currentRow;
	sf::Vector2f cellSpriteScale((float)WINDOW_WIDTH / ((float)BOARD_WIDTH * (float)TEXTURE_DIRT.getSize().x),
								(float)WINDOW_HEIGHT / ((float)BOARD_HEIGHT * (float)TEXTURE_DIRT.getSize().y));
	


	for (int y = 0; y < BOARD_HEIGHT; y++) {
		currentRow.clear();
		for (int x = 0; x < BOARD_WIDTH; x++) {
			cell tmpCell = cell(boardMap[y*BOARD_HEIGHT + x], sf::Vector2i(x, y) , sf::Vector2f(NUM_METERS_PER_CELL * x, NUM_METERS_PER_CELL * y));
			sf::Sprite sprite;
			sprite.setTexture(tmpCell.getTexture());
			sprite.setPosition(meterToPixelCoords(tmpCell.meterPos));
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
	case START:
		return(TEXTURE_START);
	case FINISH:
		return(TEXTURE_FINISH);
	default:
		throw new std::out_of_range("Texture not found");
	}
}
