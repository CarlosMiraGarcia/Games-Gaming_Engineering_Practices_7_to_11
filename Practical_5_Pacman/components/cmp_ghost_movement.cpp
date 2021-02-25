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
	_intersection = false;
	// srand is the seed to create a random number
	srand(time(NULL));
}

void GhostMovementComponent::update(double dt) {
	std::deque<Vector2f> directions;
	std::deque<string> directionsString;
	std::deque<Vector2f> finalDirections;

	Vector2f parent_pos = _parent->getPosition();

	if (_movingDirection != "Stop") {
		//Left
		if (!checkLeft(parent_pos) && _movingDirection == "Left") {
			_movingDirection = "Stop";
		}
		// Right
		if (!checkRight(parent_pos) && _movingDirection == "Right") {
			_movingDirection = "Stop";
		}
		// Up
		if (!checkUp(parent_pos) && _movingDirection == "Up") {
			_movingDirection = "Stop";
		}
		// Down
		if (!checkDown(parent_pos) && _movingDirection == "Down") {
			_movingDirection = "Stop";
		}
	}
	if (_movingDirection == "Stop" && !_intersection) {
		//Left
		if (checkLeft(parent_pos)) {
			directions.push_back(Vector2f(-1.f, 0.f));
			directionsString.push_back("Left");
		}
		// Right
		if (checkRight(parent_pos)) {
			directions.push_back(Vector2f(1.f, 0.f));
			directionsString.push_back("Right");
		}
		// Up
		if (checkUp(parent_pos)) {
			directions.push_back(Vector2f(0.f, -1.f));
			directionsString.push_back("Up");
		}
		// Down
		if (checkDown(parent_pos)) {
			directions.push_back(Vector2f(0.f, 1.f));
			directionsString.push_back("Down");
		}
	}

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
		int ran = rand() % 2;
		_direction = finalDirections[ran];
		_movingDirection = directionsString[ran];
	}
	if (finalDirections.size() == 3) {
		int ran = rand() % 3;
		_direction = finalDirections[ran];
		_movingDirection = directionsString[ran];
	}

	ActorMovementComponent::move(_direction * (float)(_speed * dt));
	_intersection = false;
}


bool GhostMovementComponent::checkLeft(Vector2f pos) {
	return validMove(pos + Vector2f(-_ghostSize, -offset)) &&
		validMove(pos + Vector2f(-_ghostSize, offset));
}
bool GhostMovementComponent::checkRight(Vector2f pos) {
	return validMove(pos + Vector2f(_ghostSize, -offset)) &&
		validMove(pos + Vector2f(_ghostSize, offset));
}
bool GhostMovementComponent::checkUp(Vector2f pos) {
	return validMove(pos + Vector2f(-offset, -_ghostSize)) &&
		validMove(pos + Vector2f(offset, -_ghostSize));
}
bool GhostMovementComponent::checkDown(Vector2f pos) {
	return validMove(pos + Vector2f(-offset, _ghostSize)) &&
		validMove(pos + Vector2f(offset, _ghostSize));
}



