#include "Player.h"
#include "game.h"

using namespace sf;
using namespace std;

void Player::Update(double dt) {

	// Player controls
	if (Keyboard::isKeyPressed(controls[0])) {
		move(getPosition());
	}
	if (Keyboard::isKeyPressed(controls[1])) {
		move(getPosition());
	}
	if (Keyboard::isKeyPressed(controls[2])) {
		move(getPosition());
	}
	if (Keyboard::isKeyPressed(controls[3])) {
		move(getPosition());
	}

	Entity::Update(dt);
}

Player::Player()
	: _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
	_shape->setFillColor(Color::Magenta);
	_shape->setOrigin(Vector2f(25.f, 25.f));
}

void Player::Render(sf::RenderWindow& window) const {
	window.draw(*_shape);
}