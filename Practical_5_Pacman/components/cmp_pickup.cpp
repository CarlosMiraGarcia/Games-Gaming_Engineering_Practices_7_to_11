#include "cmp_pickup.h"
#include "Renderer.h"
#include "cmp_sprite.h"
#include "LevelSystem.h"

PickupComponent::PickupComponent(Entity* p, bool big)
	: Component(p), _shape(std::make_shared<sf::CircleShape>()) {
}

void PickupComponent::update(double) {
	_shape->setPosition(_parent->getPosition());
	//for (...) {       //every entity in the scene
	//    if (...) {      //within 30.f unit of me
	//        ...               //get the entity ActorMovementComponent, if it has one
	//            if (...) {        //if it has one
	//              // nom nom
	//                ...                      //speed the entity up
	//                    _parent->setForDelete(); //delete myself
	//                break;                   //stop looking
	//            }
	//    }
	//}
}

void PickupComponent::render() { Renderer::queue(_shape.get()); }
sf::Shape& PickupComponent::getShape() const { return *_shape; }



