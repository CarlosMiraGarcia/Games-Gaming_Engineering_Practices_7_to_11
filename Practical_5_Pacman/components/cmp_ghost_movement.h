#pragma once
#pragma once
#include "ecm.h"
#include "cmp_actor_movement.h"

using namespace sf;
using namespace std;

class GhostMovementComponent : public ActorMovementComponent {
protected:
	sf::Vector2f _direction;
	enum state { ROAMING, ROTATING, ROTATED };
	float offset;
	state _state;

public:
	explicit GhostMovementComponent(Entity* p);
	void update(double dt) override;
};


