#pragma once
#include "Entity.h"

class Player : public Entity {
private:
	float _speed;
	float _direction;
	bool _finished;

public:
	void Update(double dt) override;
	bool validMove(sf::Vector2f pos);
	Player();
	void Render(sf::RenderWindow & window) const override;
};