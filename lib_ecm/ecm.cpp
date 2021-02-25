#include "ecm.h"

using namespace std;

Entity::Entity()
	: _position({ 0, 0 }), _rotation(0), _alive(true), _visible(true),
	_fordeletion(false) {
}

void Entity::update(double dt) {
	if (!_alive) {
		return;
	}
	for (size_t i = 0; i < _components.size(); i++) {
		if (_components[i]->is_fordeletion()) {
			_components.erase(_components.begin() + i);
			// We decrease i because we deleted a component, hence
			// the size of the vector of components is decreased.
			--i;
		}
		_components[i]->update(dt);
	}
}

bool Entity::is_fordeletion() const { return _fordeletion; }

void Entity::render() {
	if (!_visible) {
		return;
	}
	for (auto& c : _components) {
		c->render();
	}
}

const sf::Vector2f& Entity::getPosition() const { return _position; }

void Entity::setPosition(const sf::Vector2f& _position) {
	Entity::_position = _position;
}

float Entity::getRotation() const { return _rotation; }

void Entity::setRotation(float _rotation) { Entity::_rotation = _rotation; }

bool Entity::isAlive() const { return _alive; }

void Entity::setAlive(bool _alive) { Entity::_alive = _alive; }

void Entity::setForDelete() {
	_alive = false;
	_fordeletion = true;
	_visible = false;
}

bool Entity::isVisible() const { return _visible; }

void Entity::setVisible(bool _visible) { Entity::_visible = _visible; }

Component::Component(Entity* const p) : _parent(p), _fordeletion(false) {}

Entity::~Entity() {}

Component::~Component() {}

bool Component::is_fordeletion() const { return _fordeletion; }

void EntityManager::update(double dt) {
	for (size_t i = 0; i < list.size(); i++) {
		if (list[i]->is_fordeletion()) {
			list.erase(list.begin() + i);
			// We decrease i because the list is also reduced by 1
			--i;
			continue;
		}
		if (list[i]->isVisible()) {
			list[i]->update(dt);
		}
	}
}

void EntityManager::render() {
	for (auto& e : list) {
		if (e->isAlive()) {
			e->render();
		}
	}
}