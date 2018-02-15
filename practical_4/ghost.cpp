#include "ghost.h"
#include <iostream>
using namespace std;
using namespace sf;

int maxIndex = 4;
int minIndex = 1;
int randIndex = 1 + (rand() % static_cast<int>(4 - 1 + 1));

void Ghost::update(double dt) {
	// Move randomly

	switch (randIndex) {
	case 1:
		Ghost::_position.x -= Ghost::_speed * (float)dt;
		break;
	case 2:
		Ghost::_position.x += Ghost::_speed * (float)dt;
		break;
	case 3:
		Ghost::_position.y -= Ghost::_speed * (float)dt;
		break;
	case 4:
		Ghost::_position.y += Ghost::_speed * (float)dt;
		break;
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