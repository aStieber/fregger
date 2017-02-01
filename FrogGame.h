#pragma once
#include "fregger.h"
#include "board.h"
#include "entity.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

class game {
public:
	game(bool neuralNetMode, sf::RenderWindow* _window);
	

	void nextPhysicsFrame(sf::Time& gameTimeAcc, player& freg, entityManager& eManager, sf::Event& event, std::vector<sf::Keyboard::Key>& keys);
private:
	std::vector<sf::Keyboard::Key> collectInputsFromKeyboard();
	void updateWindow(player& freg, entityManager& eManager, sf::Time& windowRefreshTimeAcc);



	sf::RenderWindow* window;
	short status;


	const sf::Time gameInterval = sf::milliseconds(8);
	const sf::Time windowRefreshInterval = sf::milliseconds(8);

	board b;
	sf::Clock clock;

};
