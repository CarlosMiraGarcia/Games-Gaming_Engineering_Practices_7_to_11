#include "LevelSystem.h"
#include "Ghost.h"
#include "game.h"
#include <time.h>
#include <iostream>
#include <deque>

using namespace sf;
using namespace std;

string ghostDirection = "Up";
int randomInt = 2;
float offset = 0.f;


//Ghost.cpp
bool Ghost::validMove(sf::Vector2f pos) {
	return (ls::getTileAt(pos) == ls::WALL);
}

void Ghost::Update(double dt) {
	std::deque<int> directions;

	if (!validMove(getPosition() + Vector2f(0.f, - (_ghostSize + 1.f)))) {
		//cout << getPosition() + Vector2f(0.f, -_ghostSize);
		directions.push_back(1);
	}
	if (!validMove(getPosition() + Vector2f(_ghostSize + 1.f, 0.f))) {
		//cout << ls::getTileAt(getPosition() + Vector2f(_ghostSize, 0.f));
		directions.push_back(2);
	}
	if (!validMove(getPosition() + Vector2f(0.f, _ghostSize + 1.f))) {
		//cout << ls::getTileAt(getPosition() + Vector2f(0.f, _ghostSize));
		directions.push_back(3);
	}
	if (!validMove(getPosition() + Vector2f(- (_ghostSize + 1.f), 0.f))) {
		//cout << getPosition() + Vector2f(_ghostSize, 0.f);
		directions.push_back(4);
	}

	std::deque<int> finalDirections;

	for (int i = 0; i < directions.size(); i++) {
		if (directions[i] != _direction) {
			finalDirections.push_back(directions[i]);
		}
	}
	if (finalDirections.size() == 2) {
		srand(time(NULL));
		int ran = rand() / (RAND_MAX);
		_direction = finalDirections[ran];
	}
	if (finalDirections.size() == 3) {
		srand(time(NULL));
		int ran = rand() % 2 + 1;
		_direction = finalDirections[ran];
	}
	if (_direction == 1) {
		move(sf::Vector2f(0.f, -1.0f  * _speed * dt));
	}
	if (_direction == 2) {
		move(sf::Vector2f(1.0f * _speed * dt, 0.f));
	}
	if (_direction == 3) {
		move(sf::Vector2f(0.f, 1.0f * _speed * dt));
	}
	if (_direction == 4) {
		move(sf::Vector2f(-1.0f  * _speed * dt, 0.f));
	}


	Entity::Update(dt);
}

float Ghost::getSize() {
	return _ghostSize;
}

Ghost::Ghost(const int color)
	:
	_speed(150.f), _direction(0.f), _xValue(1.f), _yValue(0.f), Entity(make_unique<CircleShape>(_ghostSize)) {
	_shape->setFillColor(Color::Color(color));
	_shape->setOrigin(_ghostSize, _ghostSize);
}

void Ghost::Render(sf::RenderWindow& window) const {
	window.draw(*_shape);
}