#include "FrogGame.h"
#include "fregger.h"





game::game(bool neuralNetMode, sf::RenderWindow* _window) {
	window = _window;
	if (neuralNetMode) {
		
	}
	else { //regular mode
		status = INGAME;
		sf::Time gameTimeAcc;
		sf::Time windowRefreshTimeAcc;
		player freg(sf::Vector2i(4, BOARD_HEIGHT - 1));
		entityManager eManager(6, 2);
		sf::Event event;

		while (true) {
			bool reset = false;
			sf::Time t = clock.restart();
			gameTimeAcc += t;
			windowRefreshTimeAcc += t;
			while (gameTimeAcc >= gameInterval && status == INGAME) {
				std::vector<sf::Keyboard::Key> fV = collectInputsFromKeyboard();
				nextPhysicsFrame(gameTimeAcc, freg, eManager, event, fV);
			}
			
			
			if (windowRefreshTimeAcc >= windowRefreshInterval) {
				updateWindow(freg, eManager, windowRefreshTimeAcc);
			}
		}
		
	}	
}

std::vector<sf::Keyboard::Key> game::collectInputsFromKeyboard() {
	std::vector<sf::Keyboard::Key> keySet;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { keySet.emplace_back(sf::Keyboard::Up); }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { keySet.emplace_back(sf::Keyboard::Down); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { keySet.emplace_back(sf::Keyboard::Left); }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { keySet.emplace_back(sf::Keyboard::Right); }
	
	return(keySet);
}


void game::nextPhysicsFrame(sf::Time& gameTimeAcc, player& freg, entityManager& eManager, sf::Event& event, std::vector<sf::Keyboard::Key>& keys) {
	freg.dirUP = 0;
	freg.dirRIGHT = 0;
	for (sf::Keyboard::Key k : keys) {
		switch (k) {
		case sf::Keyboard::Up:
			freg.dirUP = 1;
			break;
		case sf::Keyboard::Down:
			freg.dirUP = -1;
			break;
		case sf::Keyboard::Left:
			freg.dirRIGHT = -1;
			break;
		case sf::Keyboard::Right:
			freg.dirRIGHT = 1;
			break;
		default:
			break;
		}
	}

	freg.activate();

	eManager.update();
	if (eManager.checkCollisions(freg)) { status = CRUSHED; }
	else {
		switch (freg.getGroundType(b)) {
		case OOB:
			status = WENT_OOB;
			break;
		case WATER:
			status = DROWNED;
			break;
		case FINISH:
			status = WON;
			break;
		default:
			status = INGAME;
		}
	}
	gameTimeAcc -= gameInterval;
}

void game::updateWindow(player& freg, entityManager& eManager, sf::Time& windowRefreshTimeAcc) {
	//window->clear();
	window->draw(b.background);
	eManager.drawEntities(*window);
	window->draw(freg.sprite);
	if (status != INGAME) {
		switch (status) {
		case CRUSHED:
			window->draw(crushedText);
			break;
		case DROWNED:
			window->draw(drownedText);
			break;
		case WON:
			window->draw(wonText);
			break;
		case WENT_OOB:
			window->draw(oobText);
			break;
		default:
			break;
		}
	}
	window->display();
	windowRefreshTimeAcc -= windowRefreshInterval;
}
