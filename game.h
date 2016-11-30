#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

typedef std::vector<unsigned char> ByteVec;

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;



void loadTextures();

struct cell
{
public:
	cell(int _ground=0, int _xPos=-1, int _yPos=-1);
	sf::Texture& getTexture();
	int ground;
	int xPos;
	int yPos;
};

class board
{
public:
	board();
	board(ByteVec& map);
	sf::Sprite background;
	sf::RenderTexture bg;
private:
	void init(ByteVec& boardMap);
	std::vector< std::vector<cell>> gameBoard;
	
};
