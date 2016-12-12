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

class entity
{
public:
	entity();
	entity(sf::Vector2i pos);
	sf::Sprite sprite;
	sf::Vector2f pixelPos;
	sf::Vector2i boardPos;
	sf::Vector2i destinationPos;
	float speed;
	virtual void activate(board& b)=0;
protected:
	void moveX(char direction, float speed);
	sf::Texture texture;
};


class player : public entity
{
public:
	player(sf::Vector2i pos) : entity(pos) { initialize(); };
	void activate(board& b);
	
private:
	void initialize();
};

class enemy : public entity
{
public:
	enemy() : entity() {};
	enemy(sf::Vector2i pos) : entity(pos) { initialize(); };
	void activate(board& b);
private:
	void initialize();
};

class entityManager
{
public:
	entityManager(int _numOfBuses, int _difficulty, std::vector<bool> _validRows);
private:
	std::vector<entity> EntityList;
	bool getLocation(enemy& e, std::vector<bool>& _validRows);

};