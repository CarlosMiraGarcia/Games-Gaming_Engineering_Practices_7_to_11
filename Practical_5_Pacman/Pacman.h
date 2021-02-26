#pragma once
#include "Scene.h"
#include "ecm.h"
#include "maths.h"

using namespace std;

extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;
extern EntityManager _ents;

class MenuScene : public Scene {
private:
	sf::Text text;

public:
	MenuScene() = default;
	void update(double dt) override;
	void render() override;
	void load()override;
};

class GameScene : public Scene {

private:
	sf::Text text;
	sf::Clock scoreClock;
	std::shared_ptr<Entity> player;
	std::vector<std::shared_ptr<Entity>> ghosts;
	std::vector<std::shared_ptr<Entity>> nibbles;

public:
	GameScene() = default;
	void update(double dt) override;
	void render() override;
	void load() override;
	void respawn() override;
	std::shared_ptr<Entity> makeNibble(const sf::Vector2ul& nl, bool big);
};





