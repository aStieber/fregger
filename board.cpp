#include "board.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "mapgen.h"




ByteVec defaultMap = { FINISH, FINISH, FINISH, FINISH, FINISH, FINISH, FINISH, FINISH, FINISH, FINISH,
						WATER, WATER, WATER, WATER, WATER, WATER, WATER, WATER, WATER, WATER,
						WATER, WATER, WATER, WATER, WATER, WATER, WATER, WATER, WATER, WATER,
						WATER, WATER, WATER, WATER, WATER, WATER, WATER, WATER, WATER, WATER,
						WATER, WATER, WATER, WATER, WATER, WATER, WATER, WATER, WATER, WATER,
						DIRT, DIRT, DIRT, DIRT, DIRT, DIRT, DIRT, DIRT, DIRT, DIRT,
						DIRT, DIRT, DIRT, DIRT, DIRT, DIRT, DIRT, DIRT, DIRT, DIRT,
						DIRT, DIRT, DIRT, DIRT, DIRT, DIRT, DIRT, DIRT, DIRT, DIRT,
						DIRT, DIRT, DIRT, DIRT, DIRT, DIRT, DIRT, DIRT, DIRT, DIRT,
						DIRT, DIRT, DIRT, DIRT, START, DIRT, DIRT, DIRT, DIRT, DIRT };


cell::cell(int _ground, sf::Vector2i _boardPos) {
	groundType = _ground;
	boardPos = _boardPos;
}

void board::init(ByteVec& boardMap) {
	bg.create(WINDOW_WIDTH, WINDOW_HEIGHT);
	std::vector<cell> currentRow;
	sf::Vector2f cellSpriteScale((float)WINDOW_WIDTH / ((float)BOARD_WIDTH * (float)TEXTURE_DIRT.getSize().x),
								(float)WINDOW_HEIGHT / ((float)BOARD_HEIGHT * (float)TEXTURE_DIRT.getSize().y));

	for (int y = 0; y < BOARD_HEIGHT; y++) {
		currentRow.clear();
		for (int x = 0; x < BOARD_WIDTH; x++) {
			cell tmpCell = cell(boardMap[y*BOARD_HEIGHT + x], sf::Vector2i(x, y));
			sf::Sprite sprite;
			sprite.setTexture(tmpCell.getTexture());
			sprite.setPosition(meterToPixelCoords(boardPosToMeterPos(tmpCell.boardPos)));
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
	init(getPerlinMap());
	//init(defaultMap);

}

sf::Texture& cell::getTexture() {
	switch (groundType) {
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
