#include "entity.h"
#include <Windows.h>
#include <ostream>




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

	if (rand() % 2) { //starting on right
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
	sf::Vector2u tSize = TEXTURE_FREG.getSize();	
	sprite.setOrigin(sf::Vector2f(tSize.x / 2.0, tSize.y / 2.0));

	meterPos = sf::Vector2f(meterPos.x + .5, meterPos.y + .5);

	sprite.setScale(sf::Vector2f((sizeModifier * (float)WINDOW_WIDTH) / ((float)BOARD_WIDTH * (float)TEXTURE_FREG.getSize().x),
								(sizeModifier * (float)WINDOW_HEIGHT) / ((float)BOARD_HEIGHT * (float)TEXTURE_FREG.getSize().y)));
	speed = (float)NUM_METERS_PER_CELL / 40.0;
}

int player::getGroundType(board &b) {
	int y = meterPos.y / NUM_METERS_PER_CELL;
	int x = meterPos.x / NUM_METERS_PER_CELL;
	if (0 <= y && y < BOARD_HEIGHT && 0 <= x && y < BOARD_WIDTH) {
		return(b.gameBoard[y][x].groundType);
	}
	return(OOB);
}