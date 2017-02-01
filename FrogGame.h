#pragma once
#include "fregger.h"
#include "board.h"
#include "entity.h"
#include <SFML/Graphics.hpp>



class game {
public:
	game(bool neuralNetMode, sf::RenderWindow& _window);
	~game();
	
	void nextFrame();
	void initializeGame();
private:
	void runGame(sf::Time& gameTimeAcc, sf::Time& windowRefreshTimeAcc, player& freg, entityManager& eManager, sf::Event& event);
	sf::RenderWindow window;
	short status;


	const sf::Time gameInterval = sf::milliseconds(8);
	const sf::Time windowRefreshInterval = sf::milliseconds(8);

	board b;
	sf::Clock clock;

};

game::game() {
}

game::~game() {
}