#pragma once
#include <SFML/Graphics/Shape.hpp>
#include "ecm.h"

using namespace sf;
using namespace std;

class PickupComponent : public Component {

public:
	PickupComponent() = delete;
	explicit PickupComponent(Entity* p);
	void update(double dt) override;
	void render() override;
};
