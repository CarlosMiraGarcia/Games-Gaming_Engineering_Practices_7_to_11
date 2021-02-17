#include "Player.h"
#include "game.h"
#include "LevelSystem.h"
#include <iostream>

using namespace sf;
using namespace std;
int counter = 0;

//Player.cpp
bool Player::validMove(sf::Vector2f pos) {
	return (ls::getTileAt(pos) == ls::EMPTY || ls::getTileAt(pos) == ls::START
		|| ls::getTileAt(getPosition()) == ls::END);
}


void Player::Update(double dt) {

	if (ls::getTileAt(getPosition()) == ls::END && _finished == false) {
		cout << "YOU WIN" << endl;
		_finished = true;
	}
	// Player controls
	if (validMove(getPosition()) && _finished == false) {
		if (Keyboard::isKeyPressed(controls[0]) && getPosition().x >= 25) {
			_direction--;
			move(sf::Vector2f((_direction ? -1.0f : 1.0f) * _speed * dt, 0));
		}
		if (Keyboard::isKeyPressed(controls[1]) && getPosition().x <= ls::getWindowWidth() - 25) {
			_direction++;
			move(sf::Vector2f((_direction ? 1.0f : -1.0f) * _speed * dt, 0));
		}
		if (Keyboard::isKeyPressed(controls[2]) && getPosition().y >= 25) {
			_direction--;
			move(sf::Vector2f(0, (_direction ? -1.0f : 1.0f) * _speed * dt));
		}
		if (Keyboard::isKeyPressed(controls[3]) && getPosition().y <= ls::getWindowHeight() - 25) {
			_direction++;
			move(sf::Vector2f(0, (_direction ? 1.0f : -1.0f) * _speed * dt));
		}
	}		
	
	if (!validMove(getPosition())) {
		if (Keyboard::isKeyPressed(controls[0]) && getPosition().x >= 25) {
			_position = Vector2f(getPosition().x + 1, getPosition().y);
		}
		if (Keyboard::isKeyPressed(controls[1]) && getPosition().x <= ls::getWindowWidth() - 25) {
			_position = Vector2f(getPosition().x - 1, getPosition().y);

		}
		if (Keyboard::isKeyPressed(controls[2]) && getPosition().y >= 25) {
			_position = Vector2f(getPosition().x, getPosition().y + 1);

		}
		if (Keyboard::isKeyPressed(controls[3]) && getPosition().y <= ls::getWindowHeight() - 25) {
			_position = Vector2f(getPosition().x, getPosition().y - 1);
		}
		cout << "Invalid move " << counter++ << endl;
	}

	Entity::Update(dt);
}

Player::Player()
	:
	_speed(300.f), _direction(0.f), _finished(false), Entity(make_unique<CircleShape>(25.f)) {
	_shape->setFillColor(Color::Magenta);
	_shape->setOrigin(25.f, 25.f);
	//vector<Vector2ul> tile = ls::findTiles(LevelSystem::TILE::START);
	//_position = Vector2f(ls::getTilePosition(tile[0]));
	_position = Vector2f(130.f, 130.f);
}

void Player::Render(sf::RenderWindow& window) const {
	window.draw(*_shape);
}