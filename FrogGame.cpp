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
				funcVector fV = collectInputsFromKeyboard();
				nextPhysicsFrame(gameTimeAcc, freg, eManager, event, fV);
			}
			
			
			if (windowRefreshTimeAcc >= windowRefreshInterval) {
				updateWindow(freg, eManager, windowRefreshTimeAcc);
			}
		}
		
	}	
}

funcVector game::collectInputsFromKeyboard() {
	funcVector keySet;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { keySet.emplace_back([](player& p) { p.dirUP = 1; }); }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { keySet.emplace_back([](player& p) {	p.dirUP = -1; }); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { keySet.emplace_back([](player& p) {	p.dirRIGHT = -1; }); }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { keySet.emplace_back([](player& p) {	p.dirRIGHT = 1; }); }
	
	if (keySet.size() == 0) {
		
	}
	return(keySet);
}


void game::nextPhysicsFrame(sf::Time& gameTimeAcc, player& freg, entityManager& eManager, sf::Event& event, funcVector& directions) {
	for (std::function<void(player& f)>& dir : directions) { dir(freg); }
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
	window->clear();
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
