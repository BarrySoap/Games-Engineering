#include <SFML/Graphics.hpp>
#include "player.h"
#include "entity.h"
#include "levelsystem.h"
#include <iostream>

using namespace sf;
using namespace std;

const int gameWidth = 800;					// Screen Width
const int gameHeight = 600;					// Screen Height

Player* player = new Player();

bool validmove(Vector2f pos) {
	return (ls::getTileAt(pos) != ls::WALL);
}

void Load() {
	ls::loadLevelFile("res/maze_levels/maze_2.txt");

	// Print the level to the console
	for (size_t y = 0; y < ls::getHeight(); ++y) {
		for (size_t x = 0; x < ls::getWidth(); ++x) {
			std::cout << ls::getTile({ x, y });
		}
		std::cout << endl;
	}

	Vector2f pos(gameWidth / 2, gameHeight / 2);
	player->setPosition(pos);
}

void Update(RenderWindow &window) {
	// Reset clock, recalculate deltaTime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	// Check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	// Quit via ESC key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	player->update(dt);
}

void Render(RenderWindow &window) {
	ls::render(window);
	player->render(window);
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Tile Maze");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}