#include "cmp_pickup.h"
#include "Renderer.h"
#include "cmp_sprite.h"
#include "LevelSystem.h"
#include "..\Pacman.h"
#include "cmp_actor_movement.h"

PickupComponent::PickupComponent(Entity* p, bool big)
	: Component(p), _shape(std::make_shared<sf::CircleShape>()) {
}

// need to find out how to get the position of the NIBBLE
//
//
//
//
void PickupComponent::update(double) {
	//every entity in the scene 
	for (const auto& ent : _ents.list) {
		/*cout << "Character: " << ent->getPosition() << endl;
		cout << "Nibble: " << _parent->getPosition() << endl;*/
		if (((fabs(ent->getPosition().x - _parent->getPosition().x)) < 12.f) &&
			(fabs((ent->getPosition().y - _parent->getPosition().y)) < 12.f)) {

			//get the entity ActorMovementComponent, if it has one
			auto actComp = ent->GetCompatibleComponent<ActorMovementComponent>()[0];
			//if it has one
			if (actComp != NULL) {
				actComp->setSpeed(actComp->getSpeed() + 2.f);
				_parent->setForDelete();
				//stop looking
				break;
			}
		}
	}
}

void PickupComponent::render() { Renderer::queue(_shape.get()); }
sf::Shape& PickupComponent::getShape() const { return *_shape; }



