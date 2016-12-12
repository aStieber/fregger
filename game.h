#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

typedef std::vector<unsigned char> ByteVec;

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;
extern sf::Texture TEXTURE_DIRT;
extern sf::Texture TEXTURE_WATER;
extern sf::Texture TEXTURE_FREG;

extern const int BOARD_HEIGHT;
extern const int BOARD_WIDTH;

sf::Vector2f getPixelCoords(int x, int y);
sf::Vector2f getPixelCoords(sf::Vector2i v);
sf::Vector2i getBoardCoords(int x, int y);
sf::Vector2i getBoardCoords(sf::Vector2f v);


struct cell
{
public:
	cell(int _ground, sf::Vector2i _boardPos, sf::Vector2f _pixelPos);
	sf::Texture& getTexture();
	int ground;

	sf::Vector2i boardPos;
	sf::Vector2f pixelPos;
};

class board
{
public:
	board();
	board(ByteVec& map);
	sf::Sprite background;
	sf::RenderTexture bg;
	std::vector< std::vector<cell>> gameBoard;
private:
	void init(ByteVec& boardMap);
	
};
