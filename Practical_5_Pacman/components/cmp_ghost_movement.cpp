#include "cmp_ghost_movement.h"
#include "..\game.h"
#include <deque>

using namespace std;
using namespace sf;

static Clock ghostTimer;

GhostMovementComponent::GhostMovementComponent(Entity* p)
	: ActorMovementComponent(p) {
	_speed = 400.f;
	_movingDirection = "Up";
	offset = 7.25f;
	_direction = Vector2f(0.f, -1.f);
}

void GhostMovementComponent::update(double dt) {
	std::deque<Vector2f> directions;
	std::deque<string> directionsString;
	Vector2f parent_pos = _parent->getPosition();

	//Left
	if (!validMove(parent_pos + Vector2f((-_ghostSize), -offset)) &&
		!validMove(parent_pos + Vector2f(-_ghostSize, offset)) &&
		_movingDirection == "Left") {
		_movingDirection = "Stop";
	}
	// Right
	if (!validMove(parent_pos + Vector2f(_ghostSize, -offset)) &&
		!validMove(parent_pos + Vector2f(_ghostSize, offset)) &&
		_movingDirection == "Right") {
		_movingDirection = "Stop";
	}
	// Up
	if (!validMove(parent_pos + Vector2f(-offset, -_ghostSize)) &&
		!validMove(parent_pos + Vector2f(offset, -_ghostSize)) &&
		_movingDirection == "Up") {
		_movingDirection = "Stop";
	}
	// Down
	if (!validMove(parent_pos + Vector2f(-offset, _ghostSize)) &&
		!validMove(parent_pos + Vector2f(offset, _ghostSize)) &&
		_movingDirection == "Down") {
		_movingDirection = "Stop";
	}

	if (_movingDirection == "Stop") {
		//Left
		if (validMove(parent_pos + Vector2f((-_ghostSize), -offset)) &&
			validMove(parent_pos + Vector2f(-_ghostSize, offset))) {
			directions.push_back(Vector2f(-1.f, 0.f));
			directionsString.push_back("Left");
			//cout << ls::getTileAt(parent_pos + Vector2f(-_ghostSize, 0.f)) << endl;
			//cout << "left" << endl;
		}
		// Right
		if (validMove(parent_pos + Vector2f(_ghostSize, -offset)) &&
			validMove(parent_pos + Vector2f(_ghostSize, offset))) {
			directions.push_back(Vector2f(1.f, 0.f));
			directionsString.push_back("Right");
			//cout << ls::getTileAt(parent_pos + Vector2f(_ghostSize, 0.f)) << endl;
			//cout << "Right" << endl;
		}
		// Up
		if (validMove(parent_pos + Vector2f(-offset, -_ghostSize)) &&
			validMove(parent_pos + Vector2f(offset, -_ghostSize))) {
			directions.push_back(Vector2f(0.f, -1.f));
			directionsString.push_back("Up");
			//cout << ls::getTileAt(parent_pos + Vector2f(0.f, -_ghostSize)) << endl;
			//cout << "Up" << endl;
		}
		// Down
		if (validMove(parent_pos + Vector2f(-offset, _ghostSize)) &&
			validMove(parent_pos + Vector2f(offset, _ghostSize))) {
			directions.push_back(Vector2f(0.f, 1.f));
			directionsString.push_back("Down");
			//cout << ls::getTileAt(parent_pos + Vector2f(0.f, _ghostSize)) << endl;
			//cout << "Down" << endl;
		}

	}

	std::deque<Vector2f> finalDirections;

	for (int i = 0; i < directions.size(); i++) {
		if (directions[i] != _direction) {
			finalDirections.push_back(directions[i]);
		}
	}
	if (finalDirections.size() == 1) {
		_direction = finalDirections[0];
		_movingDirection = directionsString[0];
	}

	if (finalDirections.size() == 2) {
		// srand is the seed to create a random number
		srand(static_cast<unsigned int>(std::time(nullptr)));
		int ran = rand() % 2;
		_direction = finalDirections[ran];
		_movingDirection = directionsString[ran];
		//cout << "2 Directions" << endl;
		//cout << ran << endl;
	}
	if (finalDirections.size() == 3) {
		// srand is the seed to create a random number
		srand(static_cast<unsigned int>(std::time(nullptr)));
		int ran = rand() % 3;
		_direction = finalDirections[ran];
		_movingDirection = directionsString[ran];
		cout << "3 Directions" << endl;
		cout << ran << endl;
	}
	
	//cout << _movingDirection << endl;

	ActorMovementComponent::move(_direction * (float)(_speed * dt));

}

