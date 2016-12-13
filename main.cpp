#include "game.h"
#include "entity.h"
#include <SFML/Graphics.hpp>

#define BoardVector sf::Vector2i
#define PixelVector sf::Vector2f

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

sf::Texture TEXTURE_DIRT;
sf::Texture TEXTURE_WATER;
sf::Texture TEXTURE_FREG;
sf::Texture TEXTURE_PIXEL;

void loadTextures() {
	TEXTURE_DIRT.loadFromFile("images/dirt.png");
	TEXTURE_WATER.loadFromFile("images/water.png");
	TEXTURE_FREG.loadFromFile("images/freg.png");
	TEXTURE_PIXEL.loadFromFile("images/pixel.png");
}

void setDest(player& f, bool& i) {
	f.destinationPos = f.boardPos;
	i = true;
}


int WinMain() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "suck my dick jordan", sf::Style::Close);
	loadTextures();
	board b;

	sf::Clock clock;
	const sf::Time gameInterval = sf::milliseconds(8);
	const sf::Time windowRefreshInterval = sf::milliseconds(8);
	sf::Time gameTimeAcc;
	sf::Time windowRefreshTimeAcc;

	player freg(BoardVector(1, 5));

	entityManager eManager(5, 1, std::vector<bool>(BOARD_HEIGHT, true));

	bool inputDisabled = false;
	while (window.isOpen()) //main loop
	{
		sf::Time t = clock.restart();
		gameTimeAcc += t;
		windowRefreshTimeAcc += t;

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		while (gameTimeAcc >= gameInterval) {
			if (!inputDisabled) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					setDest(freg, inputDisabled);
					freg.destinationPos.y -= (freg.destinationPos.y > 0);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					setDest(freg, inputDisabled);
					freg.destinationPos.y += (freg.destinationPos.y < BOARD_HEIGHT - 1);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
					setDest(freg, inputDisabled);
					freg.destinationPos.x -= (freg.destinationPos.x > 0);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					setDest(freg, inputDisabled);
					freg.destinationPos.x += (freg.destinationPos.x < BOARD_WIDTH - 1);
				}
				else { inputDisabled = false; }
			}
			
			freg.activate(b);
			if (abs(freg.pixelPos.x - b.gameBoard[freg.destinationPos.y][freg.destinationPos.x].pixelPos.x) < (0.01 * (freg.pixelPos.x + 1)) && //+ 1 is to prevent this from failing when pixelPox.x/y == 0
				abs(freg.pixelPos.y - b.gameBoard[freg.destinationPos.y][freg.destinationPos.x].pixelPos.y) < (0.01 * (freg.pixelPos.y + 1))) {
				inputDisabled = false;
				freg.boardPos = freg.destinationPos;
				freg.sprite.setPosition(b.gameBoard[freg.destinationPos.y][freg.destinationPos.x].pixelPos);
			}
			

			eManager.update(b);

			gameTimeAcc -= gameInterval;
		}

		if (windowRefreshTimeAcc >= windowRefreshInterval) {
			window.clear();
			window.draw(b.background);
			eManager.drawEntities(window);
			window.draw(freg.sprite);
			window.display();

			windowRefreshTimeAcc -= windowRefreshInterval;
		}
	}

	return 0;
}