#include "entity.h"
#include <Windows.h>
#include <ostream>
#include <SFML/Graphics.hpp>


entityManager::entityManager(int _numOfBuses, int _difficulty, std::vector<bool> _validRows) {
	srand(time(NULL));
	difficulty = _difficulty;
	validRows = _validRows;

	for (size_t i = 0; i < _numOfBuses; i++) {
		enemy tmp;
		if (createEntity(tmp)) {
			EntityList.push_back(tmp);
		}
	}
}

bool entityManager::createEntity(enemy& e) {

	e.speed = (float)(rand() % difficulty) + ((float)(rand() % 10) / 10.0) + .2;
	if (getLocation(e)) {
		e.length = (rand() % difficulty) + (rand() % 3) + 1;
		return(createSprite(e));
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

	char direction = rand() % 1; //left is 0
	e.boardPos.x = direction ? (BOARD_WIDTH + 1) : -1;
	e.destinationPos.x = !direction ? (BOARD_WIDTH + 1) : -1;
	e.pixelPos = getPixelCoords(e.boardPos);
	e.sprite.setPosition(e.pixelPos);

	return(true);
}

bool entityManager::createSprite(enemy& e) {
	float yRatio = (float)WINDOW_HEIGHT / (float)BOARD_HEIGHT;
	float xRatio = (float)WINDOW_WIDTH / (float)BOARD_WIDTH;
	e.sprite.setTexture(TEXTURE_PIXEL);
	e.sprite.setScale(sf::Vector2f(xRatio * e.length, yRatio));
	e.sprite.setColor(sf::Color(200, rand() % 255, rand() % 255, 255));
	e.sprite.setPosition(e.pixelPos);
	return(true);

}

void entityManager::update(board& b) {
	std::vector<int> markedForDeletion;
	for (int i = 0; i < EntityList.size(); i++) {
		EntityList[i].activate(b);
		if (EntityList[i].checkIfAtDestination()) {
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
	pixelPos = getPixelCoords(pos);
	sprite.setPosition(pixelPos);
}

entity::entity() {
	boardPos = sf::Vector2i(-1, -1);
	destinationPos = boardPos;
}

bool entity::checkIfAtDestination() {
	sf::Vector2f destPixelCoords = getPixelCoords(destinationPos);
	return(abs(pixelPos.x - destPixelCoords.x) < (0.01 * (pixelPos.x + 1)) && //+ 1 is to prevent this from failing when pixelPox.x/y == 0
		abs(pixelPos.y - destPixelCoords.y) < (0.01 * (pixelPos.y + 1)));
}


bool entity::activate(board& b) {

	if (destinationPos.y < boardPos.y) {
		pixelPos.y -= speed;
	}
	else if (destinationPos.y > boardPos.y) {
		pixelPos.y += speed;
	}
	else if (destinationPos.x < boardPos.x) {
		pixelPos.x -= speed;
	}
	else if (destinationPos.x > boardPos.x) {
		pixelPos.x += speed;
	}
	else {
		return(false);
	}
	sprite.setPosition(pixelPos);
	return(true);
}

void player::initialize() {
	sprite.setTexture(TEXTURE_FREG);
	sprite.setScale(sf::Vector2f((float)WINDOW_WIDTH / ((float)BOARD_WIDTH * (float)TEXTURE_FREG.getSize().x),
								(float)WINDOW_HEIGHT / ((float)BOARD_HEIGHT * (float)TEXTURE_FREG.getSize().y)));
	speed = 2;
}