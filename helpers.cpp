#include "helpers.h"
#include <SFML/Graphics.hpp>

sf::Vector2f meterToPixelCoords(sf::Vector2f m) {
	float xBoardWindowRatio = (float)WINDOW_WIDTH / (float)BOARD_WIDTH;
	float yBoardWindowRatio = (float)WINDOW_HEIGHT / (float)BOARD_HEIGHT;
	sf::Vector2f tmp;
	tmp.x = (m.x / (float)NUM_METERS_PER_CELL) * xBoardWindowRatio;
	tmp.y = (m.y / (float)NUM_METERS_PER_CELL) * yBoardWindowRatio;
	return(tmp);
}

sf::Vector2f meterToPixelCoords(float x, float y) {
	return(meterToPixelCoords(sf::Vector2f(x, y)));
}

sf::Vector2f boardPosToMeterPos(sf::Vector2i b) {
	return(sf::Vector2f(NUM_METERS_PER_CELL * b.x, NUM_METERS_PER_CELL * b.y));
}

float meterDistance(int loc1, int loc2) {
	return((float)NUM_METERS_PER_CELL * std::abs(float(loc1) - float(loc2)));
}

float mapValue(float i, float lowerI, float upperI, float lowerO, float upperO) {
	return((i / (upperI - lowerI)) * (upperO - lowerO));
}
