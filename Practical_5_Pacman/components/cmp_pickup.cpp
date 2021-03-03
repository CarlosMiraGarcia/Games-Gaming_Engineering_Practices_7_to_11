#include "cmp_pickup.h"
#include "Renderer.h"
#include "cmp_sprite.h"
#include "LevelSystem.h"
#include "..\Pacman.h"
#include "cmp_actor_movement.h"
#include "cmp_player_movement.h"

PickupComponent::PickupComponent(Entity* p, bool isBig)
	: Component(p), _shape(std::make_shared<sf::CircleShape>()), _isBig(isBig) {
}

void PickupComponent::update(double) {

	//every entity in the scene 
	for (const auto& ent : _ents.list) {
		/*cout << "Character: " << ent->getPosition() << endl;
		cout << "Nibble: " << _parent->getPosition() << endl;*/

		if (((fabs(ent->getPosition().x - _parent->getPosition().x)) < 12.f) &&
			(fabs((ent->getPosition().y - _parent->getPosition().y)) < 12.f)) {

			auto comps = ent->GetCompatibleComponent<PlayerMovementComponent>();
			//get the entity ActorMovementComponent, if it has one
			if (comps.size() > 0) {
				auto actComp = comps[0];
				//if it has one
				if (actComp != NULL) {
					
					if (this->isBigNibble() == false) {
						GameScene::scoreValue += 50;
					}

					if (this->isBigNibble() == true) {
						ent->setPowerUp(true);
					}

					//printf("%d\n", _isBig);	

					_parent->setForDelete();
					//stop looking		
					break;
				}
			}
		}
	}
}
bool PickupComponent::isBigNibble() { return _isBig; };

void PickupComponent::render() { Renderer::queue(_shape.get()); }
sf::Shape& PickupComponent::getShape() const { return *_shape; }



