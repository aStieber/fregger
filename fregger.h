#pragma once
#include <SFML/Graphics.hpp>


extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;
extern const int NUM_METERS_PER_CELL;

extern sf::Texture TEXTURE_DIRT;
extern sf::Texture TEXTURE_WATER;
extern sf::Texture TEXTURE_FREG;
extern sf::Texture TEXTURE_PIXEL;
extern sf::Texture TEXTURE_START;
extern sf::Texture TEXTURE_FINISH;

const enum { INGAME, CRUSHED, DROWNED, WON };
const enum { DIRT, WATER, START, FINISH, VISITED}; //ground types


extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;
extern const int NUM_METERS_PER_CELL;

extern const int BOARD_WIDTH;
extern const int BOARD_HEIGHT;