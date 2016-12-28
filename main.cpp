#include "game.h"
#include "entity.h"
#include <SFML/Graphics.hpp>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
float METER_CONST;
const int NUM_METERS_PER_CELL = 1;

sf::Texture TEXTURE_DIRT;
sf::Texture TEXTURE_WATER;
sf::Texture TEXTURE_FREG;
sf::Texture TEXTURE_PIXEL;
sf::Texture TEXTURE_START;
sf::Texture TEXTURE_FINISH;

enum {INGAME, DEAD, WON};

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

void setDest(player& f, bool& i) {
	f.destinationPos = f.boardPos;
	i = true;
}

void initializeGame() {

}


int WinMain() {
	sf::Font font;
	font.loadFromFile("Inconsolata-Regular.ttf");
	sf::Text crushedText = loadText("crushed | press R", font);
	sf::Text drownedText = loadText("drowned | press R", font);
	sf::Text wonText = loadText("you won it | press R", font);

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "go to the top", sf::Style::Close);
	loadTextures();
	board b;

	reset:
	sf::Clock clock;
	const sf::Time gameInterval = sf::milliseconds(8);
	const sf::Time windowRefreshInterval = sf::milliseconds(8);
	sf::Time gameTimeAcc;
	sf::Time windowRefreshTimeAcc;

	player freg(sf::Vector2i(4, BOARD_HEIGHT - 1));

	entityManager eManager(6, 2);

	bool inputDisabled = false;
	short status = INGAME;
	while (window.isOpen()) //main loop
	{
		sf::Time t = clock.restart();
		gameTimeAcc += t;
		windowRefreshTimeAcc += t;

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.key.code == sf::Keyboard::R) {
				goto reset; //lol
			}
		}

		while (gameTimeAcc >= gameInterval && status == INGAME) {
			if (!inputDisabled) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					setDest(freg, inputDisabled);
					freg.destinationPos.y -= (freg.destinationPos.y > 0);
					freg.direction = NORTH;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					setDest(freg, inputDisabled);
					freg.destinationPos.y += (freg.destinationPos.y < BOARD_HEIGHT - 1);
					freg.direction = SOUTH;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
					setDest(freg, inputDisabled);
					freg.destinationPos.x -= (freg.destinationPos.x > 0);
					freg.direction = WEST;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					setDest(freg, inputDisabled);
					freg.destinationPos.x += (freg.destinationPos.x < BOARD_WIDTH - 1);
					freg.direction = EAST;
				}
				else { inputDisabled = false; }
				freg.destinationMeterPos = boardPosToMeterPos(freg.destinationPos);
			}
			
			if (freg.activate(b)) {
				inputDisabled = false;
				freg.boardPos = freg.destinationPos;
				freg.meterPos = boardPosToMeterPos(freg.boardPos);
				freg.sprite.setPosition(meterToPixelCoords(freg.meterPos));
			}
			

			eManager.update(b);
			if (eManager.checkCollision(freg)) { status = DEAD;	}
			if (freg.boardPos.y == 0) { status = WON; }

			gameTimeAcc -= gameInterval;
		}

		if (windowRefreshTimeAcc >= windowRefreshInterval) {
			window.clear();
			window.draw(b.background);
			eManager.drawEntities(window);
			window.draw(freg.sprite);
			if (status != INGAME) {
				if (status == DEAD) { window.draw(crushedText); }
				if (status == WON) { window.draw(wonText); }
			}
			
			window.display();

			windowRefreshTimeAcc -= windowRefreshInterval;
		}
	}

	return 0;
}