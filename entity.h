#pragma once
#include <SFML/Graphics.hpp>
#include "game.h"

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;
extern const int BOARD_WIDTH;
extern const int BOARD_HEIGHT;

extern sf::Texture TEXTURE_DIRT;
extern sf::Texture TEXTURE_WATER;
extern sf::Texture TEXTURE_FREG;
extern sf::Texture TEXTURE_PIXEL;

class entity {
public:
	entity();
	entity(sf::Vector2i pos);
	bool checkIfAtDestination();
	sf::Sprite sprite;
	
	sf::Vector2i boardPos;
	sf::Vector2f meterPos;
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
	entityManager(int _numOfBuses, int _difficulty, std::vector<bool> _validRows);
	
	void update(board& b);
	void drawEntities(sf::RenderWindow& w);
private:
	int difficulty;
	std::vector<bool> validRows;
	std::vector<enemy> EntityList;
	
	bool createEntity(enemy& e);
	bool getLocation(enemy& e);
	bool createSprite(enemy& e);

};