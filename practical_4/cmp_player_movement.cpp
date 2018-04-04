#include "cmp_player_movement.h"
#include <SFML/Graphics.hpp>
#include <iostream> // DEBUG

using namespace sf;
using namespace std;

PlayerMovementComponent::PlayerMovementComponent(Entity* p)	: ActorMovementComponent(p) {}

void PlayerMovementComponent::update(float dt) {

	// Move randomly
	sf::Vector2f d = { 0.0f, 0.0f };

	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		d.x--;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		d.x++;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		d.y--;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		d.y++;
	}
	// Normalise displacement
	float l = sqrt(d.x * d.x + d.y * d.y);
	if (l != 0) {
		d.x = d.x / l;
		d.y = d.y / l;
	}

	move((float)dt * d * _speed);

}