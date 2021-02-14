#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::Sprite {
public:
	static void Init();
	//Update Bullets
	static void Update(const float& dt);
	//Render Bullets
	static void Render(sf::RenderWindow& window);
	//Chose a bullet and use it
	static void Fire(const sf::Vector2f& pos, const bool mode);
	static float bulletAnimationCD;
	static void Animate(Bullet &b);
	~Bullet() = default;

protected:
	static unsigned char bulletPointer;
	static Bullet bullets[256];
	//Called by static Update()
	void _Update(const float& dt);
	//Not called by our code
	Bullet();
	//false= player bullet, true=Enemy bullet
	bool _mode = false;
	static bool changeAnimation;
};
