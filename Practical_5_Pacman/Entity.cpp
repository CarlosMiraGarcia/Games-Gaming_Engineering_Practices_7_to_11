#include "Entity.h"

using namespace sf;
using namespace std;

const Vector2f Entity::getPosition() { return _position; }
void Entity::setPosition(const Vector2f& pos) { _position = pos; }
void Entity::move(const Vector2f& pos) { _position += pos; }
void Entity::Update(const double dt) {
	_shape->setPosition(_position);
}
void Entity::Render(sf::RenderWindow& window) const{}

Entity::Entity(unique_ptr<Shape> s) : _shape(std::move(s)) {}

void EntityManager::update(double dt) {
	for (auto& c : list) {
		c->Update(dt);
	}
}

void EntityManager::render(sf::RenderWindow& window) {
	for (const auto &c : list) {
		c->Render(window);
	}
}
