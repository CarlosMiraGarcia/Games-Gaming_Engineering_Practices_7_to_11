#include "cmp_ghost_movement.h"
#include "cmp_player_movement.h"
#include "..\game.h"
#include <deque>
#include "../Pacman.h"

using namespace std;
using namespace sf;
static const Vector2i directions[] = { {1, 0}, {0, 1}, {0, -1}, {-1, 0} };

GhostMovementComponent::GhostMovementComponent(Entity* p)
	: ActorMovementComponent(p) {
	_speed = 100.f;
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
		if (LevelSystem::getTileAt(position - inFront) == LevelSystem::INTERSECTION ||
			LevelSystem::getTileAt(position + inFront) == LevelSystem::WALL) {
			_state = ROTATING;
		}
		else {
			move(_direction * movementValue);
		}
		break;

	case ROTATING:
		while (newDirection == badDirection ||
			LevelSystem::getTileAt(position + (Vector2f(newDirection) * _ghostSize)) == LevelSystem::WALL) {
			auto dir = findPlayer(position);
			newDirection = dir;
		}

		_direction = Vector2f(newDirection);
		_state = ROTATED;
		break;

	case ROTATED:
		//have we left the waypoint?
		if (LevelSystem::getTileAt(position - (_direction * _ghostSize)) != LevelSystem::INTERSECTION) {
			_state = ROAMING; //yes
		}
		move(_direction * movementValue); //No
		break;
	}
}

Vector2i GhostMovementComponent::findPlayer(Vector2f ghostPosition) {
	for (auto& e : _ents.list) {
		auto comps = e->GetCompatibleComponent<PlayerMovementComponent>();
		if (comps.size() > 0) {
			auto actComp = comps[0];
			const Vector2f playerPosition = e->getPosition();
			const Vector2f wherePlayer = ghostPosition - playerPosition;
			vector<Vector2f> newDirections;

			if (wherePlayer.x > 0) {
				newDirections.push_back(Vector2f(-1, 0));
			}
			if (wherePlayer.x < 0) {
				newDirections.push_back(Vector2f(1, 0));
			}
			if (wherePlayer.y > 0) {
				newDirections.push_back(Vector2f(0, -1));
			}
			if (wherePlayer.y < 0) {
				newDirections.push_back(Vector2f(0, 1));
			}
			auto ran = rand() % 2;
			auto returnDirection = Vector2i(newDirections[ran]);

			if (LevelSystem::getTileAt(ghostPosition + (Vector2f(returnDirection) * _ghostSize)) == LevelSystem::WALL) {
				if (ran == 0) {
					if (!LevelSystem::getTileAt(ghostPosition + (Vector2f(newDirections[1]) * _ghostSize)) == LevelSystem::WALL) {
						returnDirection = Vector2i(newDirections[1]);
					}
					if (!LevelSystem::getTileAt(ghostPosition + (Vector2f(newDirections[0]) * _ghostSize)) == LevelSystem::WALL) {
						returnDirection = Vector2i(newDirections[0]);
					}
					else {
						returnDirection = returnDirection * -1;
					}
				}

				else {
					if (!LevelSystem::getTileAt(ghostPosition + (Vector2f(newDirections[0]) * _ghostSize)) == LevelSystem::WALL) {
						returnDirection = Vector2i(newDirections[0]);
					}
					if (!LevelSystem::getTileAt(ghostPosition + (Vector2f(newDirections[1]) * _ghostSize)) == LevelSystem::WALL) {
						returnDirection = Vector2i(newDirections[1]);
					}
					else {
						returnDirection = returnDirection * -1;
					}
				}
			}
			return returnDirection;
		}
	}
}