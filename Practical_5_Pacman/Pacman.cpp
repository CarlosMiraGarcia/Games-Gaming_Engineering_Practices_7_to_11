#include <SFML/Graphics.hpp>
#include "LevelSystem.h"
#include "Scene.h"
#include "Pacman.h"
#include "Renderer.h"
#include "game.h"
#include "ecm.h"
#include "components/cmp_sprite.h"
#include "components/cmp_player_movement.h"
#include "components/cmp_ghost_movement.h"

sf::Font font;
std::shared_ptr<Scene> gameScene;
std::shared_ptr<Scene> menuScene;
std::shared_ptr<Scene> activeScene;
EntityManager _ents;
static Clock keboardTime;

void MenuScene::load() {
	keboardTime.restart();
	//Load font-face from res direction
	font.loadFromFile("res/Fira.otf");
	// Set titleText properties
	text.setFont(font);
	text.setCharacterSize(70);
	// Centering titleText
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.width / 2, textRect.height / 2);
	text.setPosition(sf::Vector2f(ls::getWindowWidth() / 10, ls::getWindowHeight() / 3));
}

void MenuScene::update(double dt) {
	//Using a timer will allow me to use the same key to switch between scenes
	//It is needed to leave some miliseconds between switches, otherwise it will
	//take everystroke for everyframe since the game updates several times per
	//second
	Time timeElapsed = keboardTime.getElapsedTime();
	if (timeElapsed.asSeconds() >= 0.2) {
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			activeScene = gameScene;
			timeElapsed += keboardTime.restart();
		}
	}

	text.setString("Almost Pacman");
}

void MenuScene::render() {
	Renderer::queue(&text);
}

void GameScene::load() {
	{
		ls::setColor(ls::TILE::WALL, sf::Color::Color(0x002121DEff));
		ls::loadLevelFile("res/pacman.txt", _tileSize);

		auto player = make_shared<Entity>();
		auto s = player->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(_playerSize);
		s->getShape().setFillColor(Color::Yellow);
		s->getShape().setOrigin(Vector2f(_playerSize, _playerSize));
		vector<Vector2ul> tile = ls::findTiles(ls::TILE::START);
		player->setPosition(Vector2f(ls::getTilePosition(tile[0]) + Vector2f(_playerSize, _playerSize)));
		player->addComponent<PlayerMovementComponent>();

		_ents.list.push_back(player);
	}

	const sf::Color ghost_cols[]{ {208, 62, 25},    // red Blinky
								 {219, 133, 28},    // orange Clyde
								 {70, 191, 238},    // cyan Inky
								 {234, 130, 229} }; // pink Pinky

	for (int i = 0; i < 4; ++i) {
		auto ghost = make_shared<Entity>();
		auto s = ghost->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(_ghostSize);
		s->getShape().setFillColor(ghost_cols[i % 4]);
		s->getShape().setOrigin(Vector2f(_ghostSize, _ghostSize));
		vector<Vector2ul> tile = ls::findTiles(ls::TILE::ENEMY);
		ghost->setPosition(Vector2f(ls::getTilePosition(tile[i]) + Vector2f(_ghostSize, _ghostSize)));
		ghost->addComponent<GhostMovementComponent>();		

		_ents.list.push_back(ghost);
	}

	// Print the level to the console
	for (size_t y = 0; y < ls::getHeight(); ++y) {
		for (size_t x = 0; x < ls::getWidth(); ++x) {
			cout << ls::getTile({ x, y });
		}
		cout << endl;
	}
}

void GameScene::update(double dt) {
	//Using a timer will allow me to use the same key to switch between scenes
	//It is needed to leave some miliseconds between switches, otherwise it will
	//take everystroke for everyframe since the game updates several times per
	//second
	Time timeElapsed2 = keboardTime.getElapsedTime();
	if (timeElapsed2.asSeconds() >= 0.2) {
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			activeScene = menuScene;
			timeElapsed2 += keboardTime.restart();
		}
	}

	_ents.update(dt);
}

void GameScene::render() {
	ls::Render(Renderer::getWindow());
	_ents.render();
}

void GameScene::respawn() {
	load();
}