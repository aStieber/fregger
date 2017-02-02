#pragma once
#include "fregger.h"
#include "board.h"
#include "entity.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

class game {
public:
	game(bool _neuralNetMode, sf::RenderWindow* _window);


	void nextPhysicsFrame(sf::Time& gameTimeAcc, player& freg, busManager& eManager, std::vector<sf::Keyboard::Key>& keys, bool& reset);
	void resetGame();
	void setInputs(std::vector<sf::Keyboard::Key> keys);

	board* getBoard();
	double getFitness();
	busManager* getBuses();
private:
	std::vector<sf::Keyboard::Key> collectInputsFromDevices();
	void updateWindow(player& freg, busManager& eManager, sf::Time& windowRefreshTimeAcc);



	sf::RenderWindow* window;
	bool neuralNetMode;
	short status;


	const sf::Time gameInterval = sf::milliseconds(8);
	const sf::Time windowRefreshInterval = sf::milliseconds(8);

	board b;
	sf::Clock clock;

};