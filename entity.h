#pragma once
#include <SFML/Graphics.hpp>
#include "board.h"
#include "fregger.h"


class entity {
public:
	entity();
	entity(sf::Vector2i pos);
	sf::Sprite sprite;
	
	sf::Vector2i initializePosition;
	sf::Vector2f meterPos;
	short dirUP = 0;
	short dirRIGHT = 0;
	float speed;
	bool activate();
	int length = 1;
protected:
	sf::Texture texture;
};


class player : public entity {
public:
	player(sf::Vector2i pos) : entity(pos) { initialize(); };
	int getGroundType(board& b);
	float sizeModifier = 1.0;
private:
	void initialize();
};

class enemy : public entity {
public:
	enemy() : entity() {};
	enemy(sf::Vector2i pos) : entity(pos) {};
	
};

class entityManager {
public:
	entityManager(int _numOfBuses, int _difficulty);
	void update();
	void drawEntities(sf::RenderWindow& w);
	bool checkCollisions(player& freg);
private:
	int difficulty;
	std::vector<bool> validRows;
	std::vector<enemy> EntityList;
	
	bool createEntity(enemy& e);
	bool getLocation(enemy& e);
	bool createSprite(enemy& e);
	void delayEntrance(enemy& e);


};