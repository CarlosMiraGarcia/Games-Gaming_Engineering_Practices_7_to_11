#include "LevelSystem.h"
#include "Player.h"
#include "game.h"
#include <iostream>

using namespace sf;
using namespace std;
int counter = 0;

//Player.cpp
bool Player::validMove(sf::Vector2f pos) {
	return (ls::getTileAt(pos) == ls::EMPTY || ls::getTileAt(pos) == ls::START
		|| ls::getTileAt(pos) == ls::END);
}

void Player::Update(double dt) {

	if (ls::getTileAt(getPosition()) == ls::END && _finished == false) {
		cout << "YOU WIN" << endl;
		_finished = true;
	}
	// Player controls
	if (_finished == false) {
		if (Keyboard::isKeyPressed(controls[0]) && getPosition().x >= _playerSize) {
			if (validMove(getPosition() + Vector2f(-_playerSize, 0.f))) {
				_direction--;
				move(sf::Vector2f((_direction ? -1.0f : 1.0f) * _speed * dt, 0));
			}
		}
		if (Keyboard::isKeyPressed(controls[1]) && getPosition().x <= ls::getWindowWidth() - _playerSize) {
			if (validMove(getPosition() + Vector2f(_playerSize, 0.f))) {
				_direction++;
				move(sf::Vector2f((_direction ? 1.0f : -1.0f) * _speed * dt, 0));
			}			
		}
		if (Keyboard::isKeyPressed(controls[2]) && getPosition().y >= _playerSize){
			if (validMove(getPosition() + Vector2f(0.f, - _playerSize))) {
				_direction--;
				move(sf::Vector2f(0, (_direction ? -1.0f : 1.0f) * _speed * dt));
			}
		}
		if (Keyboard::isKeyPressed(controls[3]) && getPosition().y <= ls::getWindowHeight() - _playerSize) {
			if (validMove(getPosition() + Vector2f(0.f, _playerSize))) {
				_direction++;
				move(sf::Vector2f(0, (_direction ? 1.0f : -1.0f) * _speed * dt));
			}
		}
	}		
	
	if (!validMove(getPosition())) {
		cout << "Invalid move " << counter++ << endl;
	}

	Entity::Update(dt);
}

bool Player::isFinished() {
	return _finished;
}

float Player::getSize() {
	return _playerSize;
}

Player::Player()
	:
	_speed(500.f), _direction(0.f), _finished(false), Entity(make_unique<CircleShape>(_playerSize)) {
	_shape->setFillColor(Color::Magenta);
	_shape->setOrigin(_playerSize, _playerSize);
	//_position = Vector2f(130.f, 130.f);
}

void Player::Render(sf::RenderWindow& window) const {
	window.draw(*_shape);
}