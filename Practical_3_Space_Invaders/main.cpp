#include <SFML/Graphics.hpp>
#include "game.h"
#include "bullet.h"
#include <iostream>

using namespace sf;
using namespace std;

sf::Texture spritesheet;
std::vector<Ship*> ships;

unsigned char* bulletPointer;
std::vector<Bullet*> bullets;

Player* player;

sf::Text scoreText;
sf::Text scoreValueText;
sf::Text titleText;
sf::Text gameOver;
sf::Font font;
int scoreValue;
bool isOver;


void GameOver(RenderWindow& window) {
	window.draw(gameOver);
}

void Load() {
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
		cerr << "Failed to load spritesheet!" << std::endl;
	}

	// Populate the ship array with different invaders
	for (int r = invaders_rows; r >= 1; r--) {
		for (int c = invaders_columns; c >= 1; c--) {
			Invader* inv = new Invader();

			if (r <= 2) {
				inv = new Invader(sf::IntRect(128, 0, 32, 32), { gameWidth - c * 40.f, r * 30.f + 26 });
			}

			if (r > 2 && r <= 4) {
				inv = new Invader(sf::IntRect(64, 0, 32, 32), { gameWidth - c * 40.f, r * 30.f + 26 });
			}

			if (r > 4 && r <= 10) {
				inv = new Invader(sf::IntRect(0, 0, 32, 32), { gameWidth - c * 40.f, r * 30.f + 26 });
			}
			ships.push_back(inv);
		}
	}

	player = new Player();
	ships.push_back(player);

	Bullet::Init();

	//Load font-face from res direction
	font.loadFromFile("res/Fira.otf");
	// Set titleText properties
	titleText.setFont(font);
	titleText.setCharacterSize(28);
	titleText.setFillColor(sf::Color::Green);
	titleText.setString("Space Invaders");	

	// Centering titleText
	sf::FloatRect titleRect = titleText.getLocalBounds();
	titleText.setOrigin(titleRect.width / 2, titleRect.height / 2);
	titleText.setPosition(sf::Vector2f(gameWidth / 2, 14.0f));
	
	// Set scoreText and scoreValueText properties
	scoreText.setFont(font);
	scoreText.setCharacterSize(18);
	scoreText.setFillColor(sf::Color::Green);
	scoreText.setString("Score: ");
	scoreValueText.setFont(font);
	scoreValueText.setCharacterSize(18);
	scoreValueText.setFillColor(sf::Color::Green);
	scoreValueText.setString(to_string(scoreValue));

	// Positioning scoreText and scoreValueText
	sf::FloatRect scoreRect = scoreText.getLocalBounds();
	scoreText.setOrigin(0, scoreRect.height / 2);
	scoreText.setPosition(sf::Vector2f(10.0f, 10.0f));

	sf::FloatRect scoreValueRect = scoreText.getLocalBounds();
	scoreValueText.setOrigin(0, scoreValueRect.height / 2);
	scoreValueText.setPosition(sf::Vector2f(scoreText.getPosition().x + scoreRect.width + 2, scoreText.getPosition().y));

	// Set gameOver properties
	gameOver.setFont(font);
	gameOver.setCharacterSize(150);
	gameOver.setFillColor(sf::Color::White);
	gameOver.setString("GAME OVER");

	// Centering titleText
	sf::FloatRect gameOverRect = gameOver.getLocalBounds();
	gameOver.setOrigin(gameOverRect.width / 2, gameOverRect.height / 2);
	gameOver.setPosition(sf::Vector2f(gameWidth / 2, gameHeight / 2 - 50));
}


void Update(RenderWindow& window) {
	// Reset clock, recalculate deltatime
	static Clock clockDelta;
	float dt = clockDelta.restart().asSeconds();

	// Check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}
	
	// Animation timer decreases with delta time
	Invader::animationCoolDown -= dt;
	Bullet::bulletAnimationCD -= dt;

	// We update each of the ships inside the ship array
	for (auto& s : ships) {
		if (!s-> is_gameOver()){ 
			s->Update(dt); }

		else {
			GameOver(window);
		}
	}

	// Check if animation timer is less than 0, then reset it
	if (Invader::animationCoolDown < 0) {
		Invader::animationCoolDown = 0.6f;
	}



	// Update bullet class
	Bullet::Update(dt);

	if (Bullet::bulletAnimationCD < 0) {
		Bullet::bulletAnimationCD = 0.1f;
	}
	// Keyboard binds
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	scoreValueText.setString(to_string(scoreValue));
}


void Render(RenderWindow& window) {
	for (const auto s : ships) {
		window.draw(*s);
	}
	Bullet::Render(window);
	window.draw(titleText);
	window.draw(scoreText);
	window.draw(scoreValueText);
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Space Invaders");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}