#include "player.h"
#include "system_renderer.h"

using namespace sf;
using namespace std;

void Player::update(float dt) {
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

Player::Player() : 
	_speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
	_shape->setFillColor(Color::Yellow);
	_shape->setOrigin(Vector2f(25.f, 25.f));
}

void Player::render(sf::RenderWindow &window) const {
	Renderer::queue(_shape.get());
}