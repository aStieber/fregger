#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "helpers.h"

typedef std::vector<unsigned char> ByteVec;

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;
extern const int NUM_METERS_PER_CELL;
extern sf::Texture TEXTURE_DIRT;
extern sf::Texture TEXTURE_WATER;
extern sf::Texture TEXTURE_FREG;

extern const int BOARD_HEIGHT;
extern const int BOARD_WIDTH;

struct cell {
public:
	cell(int _ground, sf::Vector2i _boardPos, sf::Vector2f _pixelPos);
	sf::Texture& getTexture();
	int ground;

	sf::Vector2i boardPos;
	sf::Vector2f meterPos;
};

class board {
public:
	board();
	sf::Sprite background;
	sf::RenderTexture bg;
	std::vector< std::vector<cell>> gameBoard;
private:
	void init(ByteVec& boardMap);

};
