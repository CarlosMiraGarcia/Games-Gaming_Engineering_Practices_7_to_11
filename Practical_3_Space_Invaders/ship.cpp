#include "ship.h"
#include "game.h"
#include "bullet.h"
using namespace sf;
using namespace std;

bool Invader::direction;
float Player::direction;
float Invader::speed;
float Player::speed;

// Define our Ship Class
Ship::Ship() {};

Ship::Ship(sf::IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

void Ship::Update(const float& dt) {}
bool Ship::is_exploded() const { return false; }
void Ship::MoveDown() {}
void Ship::Explode() {}

// Define the ship deconstructor.
// Although we set this to pure virtual, we still have to define it
Ship::~Ship() = default;

// Define our Invader Class
Invader::Invader() : Ship() {};

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
}

void Invader::Update(const float& dt) {
	Ship::Update(dt);

	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

	if (is_exploded()) {
		fadetime -= dt;
		// If time is 0 or lower, set position of invader out of scope
		if (fadetime <= 0) {
			setPosition(-100, -100);
		}
		return;
	}

	if ((direction && getPosition().x > gameWidth - 16) || (!direction && getPosition().x < 16)) {
		direction = !direction;
		for (int i = 0; i < ships.size(); ++i) {
			ships[i]->MoveDown();
		}
	}
	static float firetime = 0.0f;
	firetime -= dt;

	if (firetime <= 0 && rand() % 100 == 0) {
		Bullet::Fire(getPosition(), true);
		firetime = 4.0f + (rand() % 60);
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

	if (is_exploded()) { return; }
	
	direction = 0.0f;
	speed = 400.f;

	if (Keyboard::isKeyPressed(controls[0]) && getPosition().x > 2) {
		direction--;
	}

	if (Keyboard::isKeyPressed(controls[1]) && getPosition().x < gameWidth - 34) {
		direction++; 
	}

	move(dt * direction * speed, 0);

	static float firetime = 0.0f;
	firetime -= dt;

	if (firetime <= 0 && Keyboard::isKeyPressed(controls[2])){
		Bullet::Fire(getPosition(), false);
		firetime = 0.7f;
	}
}