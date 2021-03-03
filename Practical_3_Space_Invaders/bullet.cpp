#include "bullet.h"
#include "ship.h"
#include "game.h"

using namespace sf;
using namespace std;

unsigned char Bullet::bulletPointer;
float Bullet::bulletAnimationCD;
bool Bullet::changeAnimation;
Bullet Bullet::bullets[256];

//Define Bullet Class
Bullet::Bullet() {};

void Bullet::Init() {
	for (auto& b : bullets) {
		b.setPosition(-100.0f, -100.0f);
		b.setTexture(spritesheet);
		b.setTextureRect(IntRect(64, 32, 32, 32));
		b.setOrigin(16, 16);
	}
}
// Check the sprite and change it for the next or previous one in order to create animation effect
void Bullet::Animate(Bullet& b) {
	if (changeAnimation) {
		b.setTextureRect(IntRect(96, 32, 32, 32));
		changeAnimation = false;
		return;
	}

	else {
		b.setTextureRect(IntRect(64, 32, 32, 32));
		changeAnimation = true;
		return;
	}
}

void Bullet::Update(const float& dt) {
	for (auto& b : bullets) {
		b._Update(dt);
		if (bulletAnimationCD <= 0) {
			Animate(b);
		}
	}
}

void Bullet::Render(sf::RenderWindow& window) {
	for (auto& b : bullets) {
		window.draw(b);
	}
}

void Bullet::Fire(const sf::Vector2f& pos, const bool mode) {
	Bullet& tempbullet = bullets[++bulletPointer];

	tempbullet.setPosition(pos);
	tempbullet._mode = mode;

	if (mode) {
		tempbullet.setTextureRect(IntRect(64, 32, 32, 32));
	}

	else {
		tempbullet.setTextureRect(IntRect(32, 32, 32, 32));
	}
}

void Bullet::_Update(const float& dt) {
	if (getPosition().y < -32 || getPosition().y > gameHeight + 32) {
		//off screen - do nothing
		return;
	}
	else {
		move(0, dt * 200.0f * (_mode ? 1.0f : -5.0f));
		const FloatRect boundingBox = getGlobalBounds();

		for (auto s : ships) {
			if (!_mode && s == player) {
				//This are player bullets and they don't collide with player
				continue;
			}

			if (_mode && s != player) {
				//This are invaders bullets and they don't collida with invaders
				continue;
			}

			if (!s->is_exploded() && s->getGlobalBounds().intersects(boundingBox)) {
				//Call Explode method
				s->Explode();
				//Warp bullet off-screen
				setPosition(-100, -100);
				if (s != player) {
					scoreValue += 50;
				}
				return;
			}
		}
	}
}