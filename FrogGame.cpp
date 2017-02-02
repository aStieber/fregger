#include "FrogGame.h"
#include "fregger.h"

game::game(bool _neuralNetMode, sf::RenderWindow* _window) {
	window = _window;
	neuralNetMode = _neuralNetMode;

	if (neuralNetMode) {
		sf::Time windowRefreshTimeAcc;

	}
	else { //regular mode
		while (true) {
			board b();
			bool reset = false;
			status = INGAME;
			sf::Time gameTimeAcc;
			sf::Time windowRefreshTimeAcc;
			player freg(sf::Vector2i(4, BOARD_HEIGHT - 1));
			busManager eManager(6, 2);
			
			while (true) {
				if (reset) { break; }

				sf::Time t = clock.restart();
				gameTimeAcc += t;
				windowRefreshTimeAcc += t;
				while (gameTimeAcc >= gameInterval) {
					std::vector<sf::Keyboard::Key> keys = collectInputsFromDevices();
					nextPhysicsFrame(gameTimeAcc, freg, eManager, keys, reset);
				}

				if (windowRefreshTimeAcc >= windowRefreshInterval) { updateWindow(freg, eManager, windowRefreshTimeAcc); }
			}
		}
	}	
}

std::vector<sf::Keyboard::Key> game::collectInputsFromDevices() {
	std::vector<sf::Keyboard::Key> keySet;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { keySet.emplace_back(sf::Keyboard::Up); }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { keySet.emplace_back(sf::Keyboard::Down); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { keySet.emplace_back(sf::Keyboard::Left); }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { keySet.emplace_back(sf::Keyboard::Right); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) { keySet.emplace_back(sf::Keyboard::R); }

	sf::Event event;
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window->close();
	}
	
	return(keySet);
}


void game::nextPhysicsFrame(sf::Time& gameTimeAcc, player& freg, busManager& eManager, std::vector<sf::Keyboard::Key>& keys, bool& reset) {
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
		case sf::Keyboard::R:
			reset = true;
			break;
		default:
			break;
		}
	}
	if (status == INGAME) {
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
	}

	
	gameTimeAcc -= gameInterval;
}

void game::updateWindow(player& freg, busManager& eManager, sf::Time& windowRefreshTimeAcc) {
	//window->clear();
	window->draw(b.background);
	eManager.drawEntities(*window);
	window->draw(freg.sprite);
	if (status != INGAME) {
		switch (status) {
		case CRUSHED:
			window->draw(CRUSHED_TEXT);
			break;
		case DROWNED:
			window->draw(DROWNED_TEXT);
			break;
		case WON:
			window->draw(WON_TEXT);
			break;
		case WENT_OOB:
			window->draw(OOB_TEXT);
			break;
		default:
			break;
		}
	}
	window->display();
	windowRefreshTimeAcc -= windowRefreshInterval;
}
