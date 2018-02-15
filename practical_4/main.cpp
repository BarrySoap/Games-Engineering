#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "ghost.h"
#include "entity.h"

using namespace sf;
using namespace std;

const int gameWidth = 800;					// Screen Width
const int gameHeight = 600;					// Screen Height

Player* player = new Player();
std::vector<Entity *> entities;

void Load() {
	Vector2f pos(gameWidth / 2, gameHeight / 2);
	player->setPosition(pos);

	entities.push_back(player);

	for (int i = 0; i < 4; i++) {
		Ghost* ghost = new Ghost();
		entities.push_back(ghost);
	}
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

	for (auto &e : entities) {
		e->update(dt);
	}
}

void Render(RenderWindow &window) {
	player->render(window);

	for (auto &e : entities) {
		e->render(window);
	}
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Pac-Man");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}