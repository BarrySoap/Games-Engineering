#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "ghost.h"
#include "entity.h"
#include "system_renderer.h"

using namespace sf;
using namespace std;

const int gameWidth = 800;					// Screen Width
const int gameHeight = 600;					// Screen Height

void Load() {
	
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
}

void Render(RenderWindow &window) {
	// Renderer::queue(&text)
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