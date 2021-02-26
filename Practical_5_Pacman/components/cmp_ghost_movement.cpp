#include "cmp_ghost_movement.h"
#include "..\game.h"
#include <deque>

using namespace std;
using namespace sf;
static const Vector2i directions[] = { {1, 0}, {0, 1}, {0, -1}, {-1, 0} };

static Clock ghostTimer;

GhostMovementComponent::GhostMovementComponent(Entity* p)
	: ActorMovementComponent(p) {
	_speed = 300.f;
	_state = ROAMING;
	_direction = Vector2f(0.f, -1.f);
	// srand is the seed to create a random number
	srand(time(NULL));
}

void GhostMovementComponent::update(double dt) {
	//amount to move
	const auto movementValue = (float)(_speed * dt);
	//Curent position
	const Vector2f position = _parent->getPosition();
	//Next position
	const Vector2f newPosition = position + _direction * movementValue;
	//Inverse of our current direction
	const Vector2i badDirection = -1 * Vector2i(_direction);
	//Random new direction
	Vector2i newDirection = directions[(rand() % 4)];
	const Vector2f inFront = _direction * _ghostSize;

	switch (_state) {
	case ROAMING:
		// Wall in front or at waypoint
		if (LevelSystem::getTileAt(position - inFront) == LevelSystem::WAYPOINT ||
			LevelSystem::getTileAt(position + inFront) == LevelSystem::WALL)
		{
			_state = ROTATING;
		}
		else {
			move(movementValue * _direction);
		}
		break;

	case ROTATING:		
		while (newDirection == badDirection || 
			LevelSystem::getTileAt(position + (Vector2f(newDirection) * _ghostSize)) == LevelSystem::WALL) {
			newDirection = directions[(rand() % 4)];
		}

		_direction = Vector2f(newDirection);
		_state = ROTATED;
		cout << LevelSystem::getTileAt(position + (Vector2f(newDirection) * _ghostSize)) << endl;
		break;

	case ROTATED:
		//have we left the waypoint?
		if (LevelSystem::getTileAt(position - (_direction * _ghostSize)) != LevelSystem::WAYPOINT) {
			_state = ROAMING; //yes
		}
		move(_direction * movementValue); //No
		break;
	}
}




