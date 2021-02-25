#include "cmp_pickup.h"
#include "Renderer.h"


void PickupComponent::update(double) {
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

void PickupComponent::render() {
}

PickupComponent::PickupComponent(Entity* p)
	: Component(p) {
}