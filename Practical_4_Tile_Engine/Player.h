#pragma once
#include "Entity.h"

class Player : public Entity {
private:
	float _speed;
	float _direction;

public:
	void Update(double dt) override;
	bool validMove(sf::Vector2f pos);
	bool isFinished();
	float getSize();
	bool _finished;
	Player();
	void Render(sf::RenderWindow & window) const override;
};