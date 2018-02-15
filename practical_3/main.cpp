#include <SFML/Graphics.hpp>
#include "player.h"
#include "entity.h"
#include "levelsystem.h"
#include <iostream>
#include <stdlib.h>

using namespace sf;
using namespace std;

const int gameWidth = 800;					// Screen Width
const int gameHeight = 600;					// Screen Height
float accumulator = 0;

Vector2f startPos(150.0f, 150.0f);				// Starting Position

Player* player = new Player();

bool validmove(Vector2f pos) {
	return (ls::getTileAt(pos) != ls::WALL);
}

bool EndGame(Vector2f pos) {
	return (ls::getTileAt(pos) == ls::END);
}

void Load() {
	ls::loadLevelFile("res/maze_levels/maze_2.txt");
	std::cout << "Level:" << std::endl;

	// Print the level to the console
	for (size_t y = 0; y < ls::getHeight(); ++y) {
		for (size_t x = 0; x < ls::getWidth(); ++x) {
			std::cout << ls::getTile({ x, y });
		}
		std::cout << endl;
	}

	player->setPosition(startPos);
}

void Update(RenderWindow &window) {
	// Reset clock, recalculate deltaTime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	accumulator += dt;
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

	if (validmove(player->getPosition()) == false) {
		std::cout << "\r" << "in wall" << std::flush;
	}

	if (EndGame(player->getPosition()) == true) {
		window.close();
	}

	if (Keyboard::isKeyPressed(Keyboard::C)) {
		system("CLS");
	}

	std::cout << "\r" << "Elapsed Time: " << accumulator << std::flush;
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