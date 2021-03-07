#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"
#include "Pacman.h"
#include "Renderer.h"
#include "ecm.h"

using namespace sf;
using namespace std;

void Load() {
	// Load Scene-Local Assets
	gameScene.reset(new GameScene());
	menuScene.reset(new MenuScene());
	gameScene->load();
	menuScene->load();
	// Start at main menu
	activeScene = gameScene;
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

	// Keyboard binds
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	activeScene->update(dt);
}
void Render(RenderWindow& window) {
	activeScene->render();
	Renderer::render();
}

int main() {
	Load();
	RenderWindow window(VideoMode(ls::getWindowWidth(), ls::getWindowHeight()), "Pacman");
	Renderer::initialise(window);
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}