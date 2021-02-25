#pragma once
#include "ecm.h"
#include "cmp_actor_movement.h"

using namespace sf;
using namespace std;

class GhostMovementComponent : public ActorMovementComponent {
private:
	Vector2f _direction;
	string _movingDirection;
	float offset;
	Vector2f oldPosition;
	bool checkUp(Vector2f vec);
	bool checkDown(Vector2f vec);
	bool checkLeft(Vector2f vec);
	bool checkRight(Vector2f vec);

public:
	explicit GhostMovementComponent(Entity* p);
	void update(double dt) override;
};
