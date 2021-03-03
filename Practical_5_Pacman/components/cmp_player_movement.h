#pragma once
#include "ecm.h"
#include "cmp_actor_movement.h"

using namespace sf;
using namespace std;

class PlayerMovementComponent : public ActorMovementComponent {
private:
	Vector2f _direction;
	float offset;
	Clock powerUpTimer;

public:
	explicit PlayerMovementComponent(Entity* p);
	void update(double dt) override;
	bool _isTimerFinished = true;
};
