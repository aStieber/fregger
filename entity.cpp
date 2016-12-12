#include "entity.h"
#include <SFML/Graphics.hpp>


entityManager::entityManager( int _numOfBuses, int _difficulty, std::vector<bool> _validRows)
{
	srand(time(NULL));

	for (size_t i = 0; i < _numOfBuses; i++)
	{
		
		enemy tmp;
		tmp.speed = (rand() % _difficulty) + 1;
		if (getLocation(tmp, _validRows))
		{
			tmp.length = (rand() % _difficulty) + (rand() % 3) + 1;
			if (createSprite(tmp))
			{
				EntityList.push_back(tmp);
			}
		}
	}

}

bool entityManager::getLocation(enemy& e, std::vector<bool>& _validRows)
{
	std::vector<int> validNums;
	for (size_t i = 0; i < _validRows.size(); i++)
	{
		validNums.push_back(i);
	}
	if (validNums.size() == 0) { return(false); }

	e.boardPos.y = validNums[rand() % validNums.size()];
	e.destinationPos = e.boardPos;

	char direction = rand() % 1; //left is 0
	e.boardPos.x = direction ? (BOARD_WIDTH + 1) : -1;
	e.destinationPos.x = !direction ? (BOARD_WIDTH + 1) : -1;

	e.pixelPos = getPixelCoords(e.boardPos);



	return(true);
}

bool entityManager::createSprite(enemy& e)
{
	float yRatio = (float)WINDOW_HEIGHT / (float)BOARD_HEIGHT;
	float xRatio = (float)WINDOW_WIDTH / (float)BOARD_WIDTH;
	e.sprite.setTexture(TEXTURE_PIXEL);
	e.sprite.setScale(sf::Vector2f(xRatio * e.length, yRatio));
	e.sprite.setColor(sf::Color(200, rand() % 255, rand() % 255, 255));
	e.sprite.setPosition(e.pixelPos);
	return(true);

}

void entityManager::update(board& b)
{
	for (enemy e : EntityList)
	{
		e.activate(b);
	}
}

void entityManager::drawEntities(sf::RenderWindow& w)
{
	for (enemy e : EntityList)
	{
		w.draw(e.sprite);
	}
}


entity::entity(sf::Vector2i pos)
{
	boardPos = pos;
	destinationPos = boardPos;
	pixelPos = getPixelCoords(pos);
	sprite.setPosition(pixelPos);
}

entity::entity()
{
	boardPos = sf::Vector2i(-1, -1);
	destinationPos = boardPos;
}

//void entity::moveX(char direction, float speed)
//{
//	char moveDistance = 2;
//	sf::Vector2f spritePos = sprite.getPosition();
//	spritePos.x += (direction * moveDistance * speed);
//	sprite.setPosition(spritePos);
//}

void entity::moveX(char direction, float speed)
{
	char moveDistance = 2;
	sf::Vector2f spritePos = sprite.getPosition();
	spritePos.x += (direction * moveDistance * speed);
	sprite.setPosition(spritePos);
}

void entity::activate(board& b)
{
	bool up = destinationPos.y < boardPos.y;
	bool down = destinationPos.y > boardPos.y;
	bool right = destinationPos.x > boardPos.x;
	bool left = destinationPos.x < boardPos.x;

	if (up)
	{
		pixelPos.y -= speed;
	}
	else if (down)
	{
		pixelPos.y += speed;
	}
	else if (left)
	{
		pixelPos.x -= speed;
	}
	else if (right)
	{
		pixelPos.x += speed;
	}
	sprite.setPosition(pixelPos);
}

void player::initialize()
{
	sprite.setTexture(TEXTURE_FREG);
	sprite.setScale(sf::Vector2f(.2, .2));
	speed = 2;
}


void enemy::initialize()
{

	sprite.setTexture(TEXTURE_FREG);
	sprite.setScale(sf::Vector2f(.2, .2));
}