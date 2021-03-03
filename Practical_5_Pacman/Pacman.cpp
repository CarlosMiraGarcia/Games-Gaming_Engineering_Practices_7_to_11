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
#include "components/cmp_pickup.h"
#include "maths.h"
#include <memory>


using namespace std;

sf::Font font;
std::shared_ptr<Scene> gameScene;
std::shared_ptr<Scene> menuScene;
std::shared_ptr<Scene> activeScene;
std::shared_ptr<Entity> player;
std::vector<shared_ptr<Entity>> ghosts;
std::vector<shared_ptr<Entity>> nibbles;
int GameScene::scoreValue;
EntityManager _ents;
static Clock keyboardTime;


void MenuScene::load() {
	keyboardTime.restart();
	//Load font-face from res direction
	font.loadFromFile("res/Fira.otf");
	// Set titleText properties
	text.setFont(font);
	text.setCharacterSize(70);
	// Centering text
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.width / 2, textRect.height / 2);
	text.setPosition(sf::Vector2f(ls::getWindowWidth() / 3, ls::getWindowHeight() / 3));
	text.setString("PAUSE");


}

void MenuScene::update(double dt) {
	//Using a timer will allow me to use the same key to switch between scenes
	//It is needed to leave some miliseconds between switches, otherwise it will
	//take everystroke for everyframe since the game updates several times per
	//second
	Time timeElapsedKeyboard = keyboardTime.getElapsedTime();
	if (timeElapsedKeyboard.asSeconds() >= 0.2) {
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			activeScene = gameScene;
			timeElapsedKeyboard += keyboardTime.restart();
		}
	}
}

void MenuScene::render() {
	Renderer::queue(&text);
}

std::shared_ptr<Entity> GameScene::makeNibble(const Vector2ul& nl, bool _isBig) {
	auto cherry = make_shared<Entity>();
	auto s = cherry->addComponent<ShapeComponent>();
	if (_isBig == true) {
		s->setShape<sf::CircleShape>(7.5f);
		s->getShape().setFillColor(Color(255, 185, 150));

		cherry->setPosition(ls::getTilePosition(nl) + Vector2f(6.f, 6.f));
	}

	else {
		s->getShape().setFillColor(Color(255, 185, 150));
		s->setShape<sf::CircleShape>(2.5f);
		cherry->setPosition(ls::getTilePosition(nl) + Vector2f(9.f, 9.f));
	}
	cherry->addComponent<PickupComponent>(_isBig);
	return cherry;
}
void GameScene::load() {
	{
		ls::setColor(ls::TILE::WALL, sf::Color::Color(0x002121DEff));
		ls::loadLevelFile("res/pacman.txt", _tileSize);

		player = make_shared<Entity>();
		auto s = player->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(_playerSize);
		s->getShape().setFillColor(Color::Yellow);
		s->getShape().setOrigin(Vector2f(_playerSize, _playerSize));
		vector<Vector2ul> tile = ls::findTiles(ls::TILE::START);
		player->setPosition(Vector2f(ls::getTilePosition(tile[0]) + Vector2f(_playerSize, _playerSize)));
		player->addComponent<PlayerMovementComponent>();
		player->setPowerUp(false);

		_ents.list.push_back(player);
	}

	for (int i = 0; i < 4; ++i) {
		auto ghost = make_shared<Entity>();
		auto s = ghost->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(_ghostSize);
		s->getShape().setFillColor(ghost_cols[i % 4]);
		s->getShape().setOrigin(Vector2f(_ghostSize, _ghostSize));
		vector<Vector2ul> tile = ls::findTiles(ls::TILE::ENEMY);
		ghost->setPosition(Vector2f(ls::getTilePosition(tile[i]) + Vector2f(_ghostSize, _ghostSize)));
		ghost->addComponent<GhostMovementComponent>();
		ghost->setName(ghost_name[i]);		

		ghosts.push_back(ghost);
		_ents.list.push_back(ghost);
	}

	createNibbles();

	// Print the level to the console
	for (size_t y = 0; y < ls::getHeight(); ++y) {
		for (size_t x = 0; x < ls::getWidth(); ++x) {
			cout << ls::getTile({ x, y });
		}
		cout << endl;
	}

	//Setting up scoreText & scoreValueText
	scoreText.setFont(font);
	scoreText.setCharacterSize(20);
	scoreValueText.setFont(font);
	scoreValueText.setCharacterSize(20);
	// Formatting scoreText
	sf::FloatRect scoreTextRect = scoreText.getLocalBounds();
	scoreText.setOrigin(scoreTextRect.width / 2, scoreTextRect.height / 2);
	scoreText.setFillColor(Color::Black);
	scoreText.setPosition(sf::Vector2f(10, 1));
	scoreText.setString("Score: ");
	sf::FloatRect scoreValueTextRect = scoreValueText.getLocalBounds();
	scoreValueText.setOrigin(scoreValueTextRect.width / 2, scoreValueTextRect.height / 2);
	scoreValueText.setFillColor(Color::Black);
	scoreValueText.setPosition(sf::Vector2f(85, 1));
	scoreValueText.setString("");
}


void GameScene::update(double dt) {
	//Using a timer will allow me to use the same key to switch between scenes
	//It is needed to leave some miliseconds between switches, otherwise it will
	//take everystroke for everyframe since the game updates several times per
	//second
	Time timeElapsed = changingColour.getElapsedTime();
	Time timeElapsedKeyboard = keyboardTime.getElapsedTime();
	if (timeElapsedKeyboard.asSeconds() >= 0.2) {
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			activeScene = menuScene;
			timeElapsedKeyboard += keyboardTime.restart();
		}
	}

	for (auto& g : ghosts) {
		if (length(g->getPosition() - player->getPosition()) < _ghostSize && !player->isPowerUp() && g->isAlive()) {
			respawn();
		}
		if (length(g->getPosition() - player->getPosition()) < _ghostSize && player->isPowerUp() && g->isAlive()) {
			g->setForDelete();
			scoreValue += 1000;
		}
	}

	for (auto& n : nibbles) {
		n->update(dt);
		if (n->isVisible()) {
		}
	}

	if (player->isPowerUp()) {
		auto p = _ents.list[0]->GetCompatibleComponent<ShapeComponent>();
		auto compP = p.back();

		for (auto& g : ghosts) {
			auto ghost = g ->GetCompatibleComponent<ShapeComponent>();
			auto compG = ghost.back();
			compG->getShape().setFillColor(Color(Color::White));
		}
		timeElapsed = changingColour.getElapsedTime();
		if (timeElapsed.asSeconds() > 0.1) {
			compP->getShape().setFillColor(Color(Color::Yellow));
		}
		if (timeElapsed.asSeconds() > 0  && timeElapsed.asSeconds() < 0.1){
			compP->getShape().setFillColor(Color(Color::Red));
		}
		if (timeElapsed.asSeconds() > 0.2) {
			changingColour.restart();
		}
	}
	if (!player->isPowerUp()) {
		auto p = _ents.list[0]->GetCompatibleComponent<ShapeComponent>();
		auto CompP = p.back();
		CompP->getShape().setFillColor(Color(Color::Yellow));

		for (auto& g : ghosts) {
			auto ghost = g->GetCompatibleComponent<ShapeComponent>();
			auto compG = ghost.back();
			switch (g->getName()) {
			case 'B':
				compG->getShape().setFillColor(Color(ghost_cols[0]));
				break;
			case 'C':
				compG->getShape().setFillColor(Color(ghost_cols[1]));
				break;
			case 'I':
				compG->getShape().setFillColor(Color(ghost_cols[2]));
				break;
			case 'P':
				compG->getShape().setFillColor(Color(ghost_cols[3]));
				break;
			default:
				break;
			}
		}
	}

	_ents.update(dt);
	scoreValueText.setString(to_string(scoreValue));
}

void GameScene::render() {
	ls::Render(Renderer::getWindow());
	Renderer::queue(&scoreText);
	Renderer::queue(&scoreValueText);

	for (auto& n : nibbles) {
		n->render();
	}

	_ents.render();
}

void GameScene::respawn() {
	auto player_spawns = ls::findTiles(ls::START);
	player->setPosition(ls::getTilePosition(player_spawns[0]) + Vector2f(_playerSize, _playerSize));
	player->GetCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(150.f);
	auto comps = player->GetCompatibleComponent<PlayerMovementComponent>();
	auto actComp = comps[0];
	player->setPowerUp(false);
	actComp->_isTimerFinished = true;

	auto ghost_spawns = ls::findTiles(ls::ENEMY);
	int i = 0;
	for (auto& g : ghosts) {
		g->setPosition(
			ls::getTilePosition(ghost_spawns[i++]) + Vector2f(_ghostSize, _ghostSize));
		g->GetCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(100.0f);
	}

	for (auto n : nibbles) {
		n->setForDelete();
		n.reset();
	}
	scoreValue = 0;
	nibbles.clear();
	createNibbles();
}
void GameScene::createNibbles() {
	auto nibbleLoc = LevelSystem::findTiles(LevelSystem::EMPTY);
	for (const auto& nl : nibbleLoc) {
		auto cherry = makeNibble(nl, false);
		nibbles.push_back(cherry);
	}
	nibbleLoc = LevelSystem::findTiles(LevelSystem::WAYPOINT);
	for (const auto& nl : nibbleLoc) {
		auto cherry = makeNibble(nl, true);
		nibbles.push_back(cherry);
	}
}



