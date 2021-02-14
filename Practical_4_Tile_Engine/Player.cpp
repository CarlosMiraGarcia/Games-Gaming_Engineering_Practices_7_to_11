#include "Player.h"
#include "game.h"
#include <iostream>

using namespace sf;
using namespace std;

void Player::Update(double dt) {

	// Player controls
	if (Keyboard::isKeyPressed(controls[0])) {
		cout << "A";
		move(sf::Vector2f(-0.001f * _speed, 0));
	}
	if (Keyboard::isKeyPressed(controls[1])) {
		cout << "D";
		move(sf::Vector2f(0.001f * _speed, 0));
	}
	if (Keyboard::isKeyPressed(controls[2])) {
		cout << "W";
		move(sf::Vector2f(0, -0.001f * _speed));
	}
	if (Keyboard::isKeyPressed(controls[3])) {
		cout << "S";
		move(sf::Vector2f(0, 0.001f * _speed));
	}

	Entity::Update(dt);
}

Player::Player()
	: _speed(100.f), Entity(make_unique<CircleShape>(25.f)) {
	_shape->setFillColor(Color::Magenta);
	_shape->setOrigin(Vector2f(0.f, 0.f));
}

void Player::Render(sf::RenderWindow& window) const {
	window.draw(*_shape);
}