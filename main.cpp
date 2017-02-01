#include "board.h"
#include "entity.h"
#include "fregger.h"
#include <sstream>
#include <SFML/Graphics.hpp>

//#define DEBUG



void loadTextures() {
	TEXTURE_DIRT.loadFromFile("images/dirt.png");
	TEXTURE_WATER.loadFromFile("images/water.png");
	TEXTURE_FREG.loadFromFile("images/freg.png");
	TEXTURE_PIXEL.loadFromFile("images/pixel.png");
	TEXTURE_START.loadFromFile("images/start.png");
	TEXTURE_FINISH.loadFromFile("images/finish.png");
}

sf::Text loadText(std::string text, sf::Font& font) {
	sf::Text tmp(text, font);
	tmp.setPosition(10, (WINDOW_HEIGHT / 2.0) - 50);
	tmp.setCharacterSize(70);
	tmp.setFillColor(sf::Color::Red);
	return(tmp);
}


int WinMain() {
	sf::Font font;
	font.loadFromFile("Inconsolata-Regular.ttf");
	sf::Text crushedText = loadText("crushed | press R", font);
	sf::Text drownedText = loadText("drowned | press R", font);
	sf::Text wonText = loadText("you won it | press R", font);
	sf::Text oobText = loadText("stay in it | press R", font);
#ifdef DEBUG
	sf::Text debugText;
#endif // DEBUG
	

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "go to the top", sf::Style::Close);
	loadTextures();

	const sf::Time gameInterval = sf::milliseconds(8);
	const sf::Time windowRefreshInterval = sf::milliseconds(8);

	while (true) {
		board b;
		sf::Clock clock;
		
		sf::Time gameTimeAcc;
		sf::Time windowRefreshTimeAcc;

		player freg(sf::Vector2i(4, BOARD_HEIGHT - 1));

		entityManager eManager(6, 2);

		short status = INGAME;
		while (window.isOpen()) //main loop
		{
			sf::Time t = clock.restart();
			gameTimeAcc += t;
			windowRefreshTimeAcc += t;

			sf::Event event;
			bool reset = false;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
					exit(0);
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) { reset = true; }
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) { exit(0); }
			}
			if (reset) { break; }

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
		

#ifdef DEBUG
				std::stringstream debugStr;
				debugStr << "x: " << freg.boardPos.x << " y: " << freg.boardPos.y << " g: " << b.gameBoard[freg.boardPos.y][freg.boardPos.x].ground;
				debugText = loadText(debugStr.str(), font);
#endif // DEBUG

				gameTimeAcc -= gameInterval;
			}
			if (windowRefreshTimeAcc >= windowRefreshInterval) {
				window.clear();
				window.draw(b.background);
				eManager.drawEntities(window);
				window.draw(freg.sprite);
#ifdef DEBUG
				window.draw(debugText);
#endif // DEBUG
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
	}
	return 0;
}