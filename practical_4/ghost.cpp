#include "ghost.h"
#include <iostream>
using namespace std;
using namespace sf;

int maxIndex = 4;
int minIndex = 1;
int randIndex = 0;
static float delay = 20.0f;

void Ghost::update(double dt) {
	// Move randomly
	delay -= (float)dt;
	randIndex = 1 + (rand() % static_cast<int>(4 - 1 + 1));

	cout << delay << std::endl;

	if (delay <= 5.0f && delay > 0.0f) {
		Ghost::_position.x -= Ghost::_speed * (float)dt;
	}
	else if (delay <= 10.0f && delay > 5.0f) {
		Ghost::_position.x += Ghost::_speed * (float)dt;
	}
	else if (delay <= 15.0f && delay > 10.0f) {
		Ghost::_position.y += Ghost::_speed * (float)dt;
	}
	else if (delay <= 20.0f && delay > 15.0f) {
		Ghost::_position.y -= Ghost::_speed * (float)dt;
	}
	else {
		delay = 20.0f;
	}

	Entity::update(dt);
}

Ghost::Ghost()
	: _speed(200.0f), Entity(make_unique<CircleShape>(25.0f)) {
	_shape->setFillColor(Color::Blue);
	_shape->setOrigin(Vector2f(25.0f, 25.0f));
}

void Ghost::render(sf::RenderWindow &window) const {
	window.draw(*_shape);
}