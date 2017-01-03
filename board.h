#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "helpers.h"
#include "fregger.h"

typedef std::vector<unsigned char> ByteVec;

struct cell {
public:
	cell(int _ground, sf::Vector2i _boardPos);
	int groundType;
	sf::Vector2i boardPos;
	sf::Texture& getTexture();
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
