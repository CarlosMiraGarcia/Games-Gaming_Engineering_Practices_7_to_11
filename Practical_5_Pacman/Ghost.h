#pragma once
#include "Entity.h"
#include <string>

class Ghost : public Entity {
private:
	float _speed;
	int _direction;
	float _xValue;
	float _yValue;

public:
	void Update(double dt) override;
	bool validMove(sf::Vector2f pos);
	float getSize();
	Ghost();
	void SetFillColor(int colour);
	void Render(sf::RenderWindow& window) const override;
};