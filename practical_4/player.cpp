#include "player.h"
#include <iostream>
using namespace std;
using namespace sf;

void Player::update(double dt) {
	// Move in four directions based on keys

	// Move left
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		Player::_position.x -= Player::_speed * (float)dt;
	}
	// Move right
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		Player::_position.x += Player::_speed * (float)dt;
	}
	// Move up
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		Player::_position.y -= Player::_speed * (float)dt;
	}
	// Move down
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		Player::_position.y += Player::_speed * (float)dt;
	}

	Entity::update(dt);

	//std::cout << "\r" << Player::_position.x << "  " << Player::_position.y << std::flush;
}

Player::Player()
	: _speed(200.0f), Entity(make_unique<CircleShape>(25.0f)) {
	_shape->setFillColor(Color::Yellow);
	_shape->setOrigin(Vector2f(25.0f, 25.0f));
}

void Player::render(sf::RenderWindow &window) const {
	window.draw(*_shape);
}