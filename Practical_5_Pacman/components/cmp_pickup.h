#pragma once
#include <SFML/Graphics/Shape.hpp>
#include "ecm.h"

using namespace sf;
using namespace std;

class PickupComponent : public Component {
protected:
	std::shared_ptr<sf::Shape> _shape;

public:
	PickupComponent() = delete;
	explicit PickupComponent(Entity* p, bool big);

	void update(double dt) override;
	void render() override;

	sf::Shape& getShape() const;

	template <typename T, typename... Targs>
	void setShape(Targs... params) {
		_shape.reset(new T(params...));
	}
};
