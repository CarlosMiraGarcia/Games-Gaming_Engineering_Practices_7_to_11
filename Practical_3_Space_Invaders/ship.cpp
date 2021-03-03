#include "ship.h"
#include "game.h"
#include "bullet.h"
#include <iostream>
using namespace sf;
using namespace std;

bool Invader::direction;
float Player::direction;
float Invader::speed;
float Player::speed;
float Invader::animationCoolDown;

// Define our Ship Class
Ship::Ship() {};

Ship::Ship(sf::IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

void Ship::Update(const float& dt) {}
bool Ship::is_exploded() const { return _exploded; }
bool Ship::is_gameOver() const { return _gameOver; }
void Ship::MoveDown() {}
void Ship::Animate() {}
void Ship::Explode() {
	setTextureRect(IntRect(128, 32, 32, 32));
	_exploded = true;
}

// Define the ship deconstructor.
// Although we set this to pure virtual, we still have to define it
Ship::~Ship() = default;

// Define our Invader Class
Invader::Invader() : Ship() {};

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
}

// Check the sprite and change it for the next or previous one in order to create animation effect
void Invader::Animate() {
	if (_sprite.left % 64 == 0) {
		_sprite.left += 32;
	}
	else {
		_sprite.left -= 32;
	}

	setTextureRect(_sprite);
}
void Invader::Update(const float& dt) {
	Ship::Update(dt);

	// Invader variables
	speed = 20.f;

	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

	// If the invader is not destroyed, the animation will change the sprite in order to create some "movement" effect
	if (!is_exploded() && animationCoolDown <= 0) {
		Animate();
	}

	// If the invader has been destroyed, we use the fadetime "timer" so we can move the invader off-screen after it
	if (is_exploded()) {
		fadetime -= dt;
		// If time is 0 or lower, set position of invader out of scope
		if (fadetime <= 0) {
			setPosition(-100, -100);
		}
		return;
	}

	if (!is_exploded()) {
		// When the invader gets to one of the y ends, they change direction and move down
		if ((direction && getPosition().x > gameWidth - 16) || (!direction && getPosition().x < 16)) {
			direction = !direction;
			for (int i = 0; i < ships.size(); ++i) {
				ships[i]->MoveDown();
			}
		}

		// Invaders bullets. Firetime uses deltatime as a counter let the player shot only after certain amount of time
		static float firetime = 0.0f;
		firetime -= dt;

		if (firetime <= 0 && rand() % 100 == 0) {
			Bullet::Fire(getPosition(), true);
			firetime = 4.0f + (rand() % 60);
		}
	}
}

void Invader::MoveDown() {
	move(0, 24);
}

Player::Player() : Ship(IntRect(160, 32, 32, 32)) {
	setPosition({ gameWidth * .5f, gameHeight - 32.f });
}

void Player::Update(const float& dt) {
	Ship::Update(dt);

	if (is_exploded()) { _gameOver = true; return; }

	// Player variables
	direction = 0.0f;
	speed = 400.f;

	// Player controls
	if (Keyboard::isKeyPressed(controls[0]) && getPosition().x > 2) {
		direction--;
	}
	if (Keyboard::isKeyPressed(controls[1]) && getPosition().x < gameWidth - 34) {
		direction++;
	}

	// Player movement
	move(dt * direction * speed, 0);

	// Player bullets. Firetime uses deltatime as a counter let the player shot only after certain amount of time
	static float firetime = 0.0f;
	firetime -= dt;

	if (firetime <= 0 && Keyboard::isKeyPressed(controls[2])) {
		Bullet::Fire(getPosition(), false);
		firetime = 0.7f;
	}
}