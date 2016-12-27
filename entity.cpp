#include "entity.h"
#include <Windows.h>
#include <ostream>
#include <SFML/Graphics.hpp>


entityManager::entityManager(int _numOfBuses, int _difficulty, std::vector<bool> _validRows) {
	srand(time(NULL));
	difficulty = std::max(_difficulty, 3);
	validRows = _validRows;
	for (size_t i = 0; i < _numOfBuses; i++) {
		enemy tmp;
		if (createEntity(tmp)) {
			EntityList.push_back(tmp);
		}
	}
}

bool entityManager::createEntity(enemy& e) {
	e.length = (rand() % difficulty) + (rand() % 3) + 1;
	
	if (getLocation(e)) {
		int distance = meterDistance(e.boardPos.x, e.destinationPos.x);
		float time = (float)(difficulty * 50) + (float)(rand() % (distance / 3));
		e.speed = distance / time; //in meters/tick
		if (createSprite(e)) {
			return(true);
		}
	}
	return(false);
}

bool entityManager::getLocation(enemy& e) {
	std::vector<int> validNums;
	for (size_t i = 0; i < validRows.size(); i++) {
		if (validRows[i]) { validNums.push_back(i); }
	}
	if (validNums.size() == 0) { return(false); }

	e.boardPos.y = validNums[rand() % validNums.size()];
	e.destinationPos = e.boardPos;

	if (rand() % 2) { //starting on right
		e.boardPos.x = (BOARD_WIDTH + e.length);
		e.destinationPos.x = (0 - e.length);
		e.direction = EAST;
	}
	else { //starting on left
		e.boardPos.x = (0 - e.length);
		e.destinationPos.x = (BOARD_WIDTH + e.length);
		e.direction = WEST;
	}

	e.meterPos = boardPosToMeterPos(e.boardPos);
	e.destinationMeterPos = meterToPixelCoords(e.meterPos);
	e.sprite.setPosition(e.destinationMeterPos);

	return(true);
}

bool entityManager::createSprite(enemy& e) {
	float yRatio = (float)WINDOW_HEIGHT / (float)BOARD_HEIGHT;
	float xRatio = (float)WINDOW_WIDTH / (float)BOARD_WIDTH;
	e.sprite.setTexture(TEXTURE_PIXEL);
	e.sprite.setScale(sf::Vector2f(xRatio * e.length, yRatio));
	e.sprite.setColor(sf::Color(200, rand() % 255, rand() % 255, 255));
	e.sprite.setPosition(meterToPixelCoords(e.meterPos));
	return(true);

}

void entityManager::update(board& b) {
	std::vector<int> markedForDeletion;
	for (int i = 0; i < EntityList.size(); i++) {
		if (EntityList[i].activate(b)) {
			markedForDeletion.push_back(i);
		}
	}
	for (int& d : markedForDeletion) {
		createEntity(EntityList[d]);
	}
}

void entityManager::drawEntities(sf::RenderWindow& w) {
	for (enemy& e : EntityList) {
		w.draw(e.sprite);
	}
}


entity::entity(sf::Vector2i pos) {
	boardPos = pos;
	destinationPos = boardPos;
	meterPos = boardPosToMeterPos(boardPos);
	destinationMeterPos = meterToPixelCoords(meterPos);
	sprite.setPosition(meterPos);
}


entity::entity() {
	boardPos = sf::Vector2i(-1, -1);
	destinationPos = boardPos;
}


bool entity::activate(board& b) {
	switch (direction) {
	case EAST:
		meterPos.x += speed;
		if (meterPos.x >= destinationMeterPos.x) { return(true); }
		break;
	case WEST:
		meterPos.x -= speed;
		if (meterPos.x <= destinationMeterPos.x) { return(true); }
		break;
	case NORTH:
		meterPos.y -= speed;
		if (meterPos.y <= destinationMeterPos.y) { return(true); }
		break;
	case SOUTH:
		meterPos.y += speed;
		if (meterPos.y >= destinationMeterPos.y) { return(true); }
		break;
	default:
		break;
	}

	sprite.setPosition(meterToPixelCoords(meterPos));
	return(false);
}

void player::initialize() {
	sprite.setTexture(TEXTURE_FREG);
	sprite.setScale(sf::Vector2f((float)WINDOW_WIDTH / ((float)BOARD_WIDTH * (float)TEXTURE_FREG.getSize().x),
								(float)WINDOW_HEIGHT / ((float)BOARD_HEIGHT * (float)TEXTURE_FREG.getSize().y)));
	speed = (float)NUM_METERS_PER_CELL / 40.0;
}