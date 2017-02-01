#include "FrogGame.h"
#include "fregger.h"


game::game(bool neuralNetMode, sf::RenderWindow& _window) {
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
		runGame(gameTimeAcc, windowRefreshTimeAcc, freg, eManager, event);
	}

	
	
}

void game::runGame(sf::Time& gameTimeAcc, sf::Time& windowRefreshTimeAcc, player& freg, entityManager& eManager, sf::Event& event) {
	bool reset = false;
	sf::Time t = clock.restart();
	gameTimeAcc += t;
	windowRefreshTimeAcc += t;

	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
			exit(0);
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) { reset = true; }
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) { exit(0); }
	}
	if (reset) { return; }

	while (gameTimeAcc >= gameInterval && status == INGAME) {
		freg.dirUP = 0;
		freg.dirRIGHT = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { freg.dirUP = 1; }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { freg.dirUP = -1; }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { freg.dirRIGHT = -1; }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { freg.dirRIGHT = 1; }

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
	if (windowRefreshTimeAcc >= windowRefreshInterval) {
		window.clear();
		window.draw(b.background);
		eManager.drawEntities(window);
		window.draw(freg.sprite);
		if (status != INGAME) {
			switch (status) {
			case CRUSHED:
				window.draw(crushedText);
				break;
			case DROWNED:
				window.draw(drownedText);
				break;
			case WON:
				window.draw(wonText);
				break;
			case WENT_OOB:
				window.draw(oobText);
				break;
			default:
				break;
			}
		}

		window.display();
		windowRefreshTimeAcc -= windowRefreshInterval;
	}

}
