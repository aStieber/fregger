#pragma once
#include <SFML/Graphics.hpp>
#include "board.h"
#include "fregger.h"


class entity {
public:
	entity();
	entity(sf::Vector2i pos);
	bool checkIfAtDestination();
	sf::Sprite sprite;
	
	sf::Vector2i boardPos;
	sf::Vector2f meterPos;
	uint8_t direction = 5;
	sf::Vector2i destinationPos;
	sf::Vector2f destinationMeterPos;
	float speed;
	bool activate(board& b);
protected:
	
	sf::Texture texture;
};


class player : public entity {
public:
	player(sf::Vector2i pos) : entity(pos) { initialize(); };
	bool isDrowned(board& b);
private:
	void initialize();
};

class enemy : public entity {
public:
	enemy() : entity() {};
	enemy(sf::Vector2i pos) : entity(pos) { initialize(); };
	int length;
private:
	void initialize();
};

class entityManager {
public:
	entityManager(int _numOfBuses, int _difficulty);
	
	void update(board& b);
	void drawEntities(sf::RenderWindow& w);
	bool checkCollision(player freg);
private:
	int difficulty;
	std::vector<bool> validRows;
	std::vector<enemy> EntityList;
	
	bool createEntity(enemy& e);
	bool getLocation(enemy& e);
	bool createSprite(enemy& e);
	void delayEntrance(enemy& e);


};