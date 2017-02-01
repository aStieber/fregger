#pragma once
#include "fregger.h"
#include "board.h"
#include "entity.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

using funcVector = std::vector<std::function<void(player& f)>>;

class game {
public:
	game(bool neuralNetMode, sf::RenderWindow* _window);
	

	void nextPhysicsFrame(sf::Time& gameTimeAcc, player& freg, entityManager& eManager, sf::Event& event, funcVector& fV);
private:
	funcVector collectInputsFromKeyboard();
	void updateWindow(player& freg, entityManager& eManager, sf::Time& windowRefreshTimeAcc);



	sf::RenderWindow* window;
	short status;


	const sf::Time gameInterval = sf::milliseconds(8);
	const sf::Time windowRefreshInterval = sf::milliseconds(8);

	board b;
	sf::Clock clock;

};
