#pragma once
#include <SFML/Graphics.hpp>



sf::Vector2f meterToPixelCoords(sf::Vector2f m);
sf::Vector2f meterToPixelCoords(float x, float y);
sf::Vector2f boardPosToMeterPos(sf::Vector2i b);
float meterDistance(int loc1, int loc2);

float mapValue(float i, float lowerI, float upperI, float lowerO, float upperO);
