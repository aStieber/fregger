#pragma once
#include <SFML/Graphics.hpp>

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;
extern const int NUM_METERS_PER_CELL;
extern sf::Texture TEXTURE_DIRT;
extern sf::Texture TEXTURE_WATER;
extern sf::Texture TEXTURE_FREG;

extern const int BOARD_HEIGHT;
extern const int BOARD_WIDTH;



sf::Vector2f meterToPixelCoords(sf::Vector2f m);
sf::Vector2f meterToPixelCoords(float x, float y);
sf::Vector2f boardPosToMeterPos(sf::Vector2i b);
float meterDistance(int loc1, int loc2);

float mapValue(float i, float lowerI, float upperI, float lowerO, float upperO);
