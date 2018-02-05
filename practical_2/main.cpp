#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ship.h"
#include "game.h"
#include "bullet.h"

using namespace sf;
using namespace std;

sf::Texture spritesheet;
sf::Sprite invader;

Ship* player;
std::vector<Ship *> ships;

void Reset()
{
	Invader::direction = true;
	Invader::speed = 30.f;
}

void Load() {
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
		cerr << "Failed to load spritesheet!" << std::endl;
	}

	invader.setTexture(spritesheet);
	invader.setTextureRect(sf::IntRect(0, 0, 32, 32));

	for (int r = 0; r < invaders_rows; r++) 
	{
		auto rect = IntRect(r * 32, 0, 32, 32);

		for (int c = 0; c < invaders_columns; c++) 
		{
			Vector2f position = Vector2f(50.0f * c, r * 50.0f);
			auto inv = new Invader(rect, position);
			inv->shipType = false;
			ships.push_back(inv);
		}
	}

	auto playerOne = new Player();
	player = playerOne;
	playerOne->shipType = true;
	ships.push_back(playerOne);

	Reset();
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

	for (auto &s : ships) {
		s->Update(dt);
	}

	Bullet::Update(dt);
}

void Render(RenderWindow &window) {
	for (const auto &s : ships) {
		window.draw(*s);
	}

	Bullet::Render(window);
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Space Invaders");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}

	return 0;
}