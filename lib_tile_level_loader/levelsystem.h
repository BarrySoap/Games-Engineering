#pragma once

#include <SFML/Graphics.hpp>
#include "maths.h"
#include <memory>
#include <string>
#include <vector>

#define ls LevelSystem

class LevelSystem {
public:
	enum TILE { EMPTY, START, END, WALL, ENEMY, WAYPOINT};

	static void loadLevelFile(const std::string&, float tileSize = 100.0f);
	static void render(sf::RenderWindow &window);
	static sf::Color getColor(TILE t);
	static void setColor(TILE t, sf::Color c);
	// Get Tile at grid coordinate
	static TILE getTile(sf::Vector2ul);
	// Get screenspace coordinate of tile
	static sf::Vector2f getTilePosition(sf::Vector2ul);
	// Get the tile at screenspace pos
	static TILE getTileAt(sf::Vector2f);
	static size_t getHeight() { return _height; }
	static size_t getWidth() { return _width; }

protected:
	static std::unique_ptr<TILE[]> _tiles;	// Internal array of tiles
	static size_t _width;	// How many tiles wide the level is
	static size_t _height;	// How many tiles high the level is
	static sf::Vector2f _offset;	// Screenspace offset of level, when rendered.
	static float _tileSize;	// Screenspace size of each tile, when rendered.
	static std::map<TILE, sf::Color> _colours;	// Colour to render each tile type

	// Array of SFML sprites of each tile
	static std::vector<std::unique_ptr<sf::RectangleShape>> _sprites;
	// Generate the _sprites array
	static void buildSprites();

private:
	LevelSystem() = delete;
	~LevelSystem() = delete;
};