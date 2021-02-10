#pragma once
#include <SFML/Graphics.hpp>

// Define our Ship Class
class Ship : public sf::Sprite {
protected:
	sf::IntRect _sprite;
	bool _exploded = false;
	bool _gameOver = false;

	//Default constructor is hidden
	Ship();

public:
	//Constructor that takes a psrite
	explicit Ship(sf::IntRect ir);
	//Pure virtual deconstructor -- makes this an abstract class and avoids undefined behaviour!
	virtual ~Ship() = 0;
	// Update, virtual so can be overridden, but not pure virtual
	virtual void Update(const float& dt);
	virtual void MoveDown();
	virtual void Animate();
	bool is_exploded() const;
	bool is_gameOver() const;
	virtual void Explode();
};

// Define our Invader Class
class Invader : public Ship {
public:
	static bool direction;
	static float speed;
	static float animationCoolDown;
	Invader(sf::IntRect ir, sf::Vector2f pos);
	Invader();
	void Update(const float& dt) override;
	void Animate() override;
	void MoveDown() override;
private:
	float fadetime = 0.5f;
};

// Define our Player Class
class Player : public Ship {
public:
	static float speed;
	static float direction;
	Player();
	void Update(const float& dt) override;
};
