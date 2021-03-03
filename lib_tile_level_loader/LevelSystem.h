#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include <maths.h>

#define ls LevelSystem

class LevelSystem {
public:
	enum TILE { EMPTY, START, END, WALL, ENEMY, WAYPOINT, INTERSECTION};

	static void loadLevelFile(const std::string&, float tileSize = 100.f);
	static void Render(sf::RenderWindow& window);
	static sf::Color getColor(TILE t);
	static void setColor(TILE t, sf::Color c);
	//Get Tile at grid coordinate
	static TILE getTile(sf::Vector2ul);
	//get the tile at screenspace pos
	static TILE getTileAt(sf::Vector2f);
	static size_t getHeight();
	static size_t getWidth();
	//Get Screenspace coordinate of tile
	static sf::Vector2f getTilePosition(sf::Vector2ul);
	static std::vector<sf::Vector2ul> findTiles(TILE);

	static size_t getTileSize();
	static size_t getWindowWidth();
	static size_t getWindowHeight();
	static sf::Vector2f getOffset();

protected:
	static std::unique_ptr<TILE[]> _tiles; //Internal array of tiles
	static size_t _width; //how many tiles wide is level
	static size_t _height; //how many tile high is level
	static sf::Vector2f _offset; //Screenspace offset of level, when rendered.
	static std::map<TILE, sf::Color> _colours; //color to render each tile type

	//Array of SFML sprites of each tile
	static std::vector<std::unique_ptr<sf::RectangleShape>> _sprites;
	static std::vector<std::unique_ptr<sf::CircleShape>> _spritesCircle;
	//Generate the _sprites array
	static void buildSprites();
	static float _tileSize; //Screenspace size of each tile, when rendered.

private:
	LevelSystem() = delete;
	~LevelSystem() = delete;
};
