#pragma once
#include "Scene.h"
#include "ecm.h"
#include "maths.h"

using namespace sf;
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
	sf::Text scoreText;
	sf::Clock scoreClock;
	std::shared_ptr<Entity> player;
	std::vector<std::shared_ptr<Entity>> ghosts;
	std::vector<std::shared_ptr<Entity>> nibbles;
	sf::Clock changingColour;
	const sf::Color ghost_cols[4]{	{255, 0, 0},		// red Blinky
									{255, 184, 82},		// orange Clyde
									{0, 255, 255},		// cyan Inky
									{255, 184, 255} };	// pink Pinky
	const char ghost_name[4]{  'B',    // red Blinky
							   'C',    // orange Clyde
							   'I',    // cyan Inky
							   'P' };  // pink Pinky
public:
	GameScene() = default;
	void update(double dt) override;
	void render() override;
	void load() override;
	void respawn() override;
	void createNibbles();
	static int scoreValue;
	sf::Text scoreValueText;
	std::shared_ptr<Entity> makeNibble(const sf::Vector2ul& nl, bool _isBig);
};





