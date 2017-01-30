#include "entity.h"
#include <Windows.h>
#include <ostream>
#include <SFML/Graphics.hpp>
#include "fregger.h"



entityManager::entityManager(int _numOfBuses, int _difficulty) {
	srand(time(NULL));
	difficulty = std::max(_difficulty, 3);
	validRows = std::vector<bool>(BOARD_HEIGHT, true);
	validRows.front() = false;
	validRows.back() = false;
	for (size_t i = 0; i < _numOfBuses; i++) {
		enemy tmp;
		if (createEntity(tmp)) {
			delayEntrance(tmp); //only done at beginning of game
			EntityList.push_back(tmp);
			validRows[tmp.initializePosition.y] = false;
		}
	}
}

bool entityManager::createEntity(enemy& e) {
	e.length = (rand() % difficulty) + (rand() % 3) + 1;
	
	if (getLocation(e)) {
		e.speed = NUM_METERS_PER_CELL / (15.0 + (rand() % 40)); //.018 to .066 if NUM_METERS == 1
		if (createSprite(e)) { return(true);}
	}
	return(false);
}

bool entityManager::getLocation(enemy& e) {
	std::vector<int> validNums;
	for (size_t i = 0; i < validRows.size(); i++) {
		if (validRows[i]) { validNums.push_back(i); }
	}
	if (validNums.size() == 0) { return(false); }

	e.initializePosition.y = validNums[rand() % validNums.size()];

	if (rand() % 3) { //starting on right
		e.initializePosition.x = (BOARD_WIDTH + e.length);
		e.dirRIGHT = -1;
	}
	else { //starting on left
		e.initializePosition.x = (0 - e.length);
		e.dirRIGHT = 1;
	}

	e.meterPos = boardPosToMeterPos(e.initializePosition);
	e.sprite.setPosition(meterToPixelCoords(e.meterPos));

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

void entityManager::delayEntrance(enemy& e) {

	int distance = rand() % 8;
	e.initializePosition.x += e.dirRIGHT * distance;

	e.meterPos = boardPosToMeterPos(e.initializePosition);
	e.sprite.setPosition(meterToPixelCoords(e.meterPos));
}

void entityManager::update() {
	std::vector<int> markedForDeletion;
	for (int i = 0; i < EntityList.size(); i++) {
		if (EntityList[i].activate()) {
			markedForDeletion.push_back(i);
			validRows[EntityList[i].initializePosition.y] = true;
		}
	}
	for (int& d : markedForDeletion) {
		createEntity(EntityList[d]);
		validRows[EntityList[d].initializePosition.y] = false;
	}
}

void entityManager::drawEntities(sf::RenderWindow& w) {
	for (enemy& e : EntityList) {
		w.draw(e.sprite);
	}
}

bool entityManager::checkCollisions(player& freg) {
	sf::Sprite fregSprite = freg.sprite;
	sf::FloatRect fB = fregSprite.getGlobalBounds();
	for (enemy& e : EntityList) {
		if (fB.intersects(e.sprite.getGlobalBounds())) { return(true); }
	}
	return false;
}


entity::entity(sf::Vector2i pos) {
	initializePosition = pos;
	meterPos = boardPosToMeterPos(initializePosition);
	sprite.setPosition(meterPos);
}

entity::entity() {
}


bool entity::activate() {
	meterPos.x += speed * dirRIGHT;
	meterPos.y -= speed * dirUP;

	sprite.setPosition(meterToPixelCoords(meterPos));
	return((meterPos.x >= (NUM_METERS_PER_CELL * (BOARD_WIDTH + length))) || ((meterPos.x <= (-1 * NUM_METERS_PER_CELL * length))) || (meterPos.y <= 0) || (meterPos.y >= (NUM_METERS_PER_CELL * BOARD_HEIGHT)));
}

void player::initialize() {
	sizeModifier = 0.8;
	sprite.setTexture(TEXTURE_FREG);
	sprite.setScale(sf::Vector2f((sizeModifier * (float)WINDOW_WIDTH) / ((float)BOARD_WIDTH * (float)TEXTURE_FREG.getSize().x),
								(sizeModifier * (float)WINDOW_HEIGHT) / ((float)BOARD_HEIGHT * (float)TEXTURE_FREG.getSize().y)));
	speed = (float)NUM_METERS_PER_CELL / 40.0;
}

int player::getGround(board &b) {
	int row = -1;
	int column = -1;
	
	float gap = NUM_METERS_PER_CELL - (NUM_METERS_PER_CELL * sizeModifier);
	if (fmod(meterPos.x, NUM_METERS_PER_CELL) <= gap) {
		column = (int)(meterPos.x / NUM_METERS_PER_CELL);
	}
	if (fmod(meterPos.y, NUM_METERS_PER_CELL) <= gap) {
		row = (int)(meterPos.y / NUM_METERS_PER_CELL);
	}
	if (row >= 0 && column >= 0) {
		return(b.gameBoard[row][column].groundType);
	}
	return(-1);
}

//int player::getGround(board &b) {
//	float gap = NUM_METERS_PER_CELL - (NUM_METERS_PER_CELL * sizeModifier);
//	int row = (fmod(meterPos.y, NUM_METERS_PER_CELL) <= gap) ? (int)(meterPos.y / NUM_METERS_PER_CELL) : -1;
//	int column = (fmod(meterPos.x, NUM_METERS_PER_CELL) <= gap) ? (int)(meterPos.x / NUM_METERS_PER_CELL) : -1;
//	if (row >= 0 && column >= 0) {
//		return(b.gameBoard[row][column].groundType);
//	}
//	return(-1);
//}



/*
#define __vand _mm_and_ps
__vec4 is mm128

bool AABox::Contains(const AABox& b) const {
	return(RangeContains(mMin, mMax, b.mMin, b.mMax));
}

bool RangeContains(const Vector& outerMin, const Vector& outerMax, const Vector& innerMin, const Vector& innerMax) {
	__vec4 a = _mm_cmpge_ps(innerMin.v4, outerMin.v4);
	__vec4 b = _mm_cmpge_ps(outerMax.v4, innerMax.v4);
	__vec4 result = __vand(a, b);

	int c = _mm_movemask_ps(result);
	const int mask = 7; // Don't care about W
	return((c & mask) == mask);
}
*/
