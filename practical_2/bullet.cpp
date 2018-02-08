#include "bullet.h"
#include "game.h"
#include <iostream>

using namespace sf;
using namespace std;

unsigned char Bullet::bulletPointer = 0;		// Fixes linking errors??
Bullet Bullet::bullets[256];

Bullet::Bullet(const sf::Vector2f & pos, const bool mode) {
	_mode = mode;
	setPosition(pos);

	if (_mode) {
		setTextureRect(IntRect(32, 32, 32, 32));
	}
	else {
		setTextureRect(IntRect(32, 32, 32, 32));
	}
}

Bullet::Bullet() : Sprite()
{
	setOrigin(16, 16);
	setTexture(spritesheet);
}

void Bullet::_Update(const float &dt) {
	if (getPosition().y < -32 || getPosition().y > gameHeight + 32) {
		return;
	}
	else {
		move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
		const FloatRect boundingBox = getGlobalBounds();

		for (auto s : ships) {
			if (!_mode && s == player) {
				// Player bullets don't collide with player
				continue;
			}
			if (_mode && s != player) {
				// Invader bullets don't collide with other invaders
				continue;
			}
			if (!s->is_exploded() &&
				s->getGlobalBounds().intersects(boundingBox)) {
				// Explode the ship
				s->Explode();
				// Warp bullet off-screen
				setPosition(-100, -100);
				return;
			}
		}
	}
};

void Bullet::Update(const float &dt)
{
	for (auto &b : bullets) {
		b._Update(dt);
	}
}

void Bullet::Render(sf::RenderWindow & window)
{
	for (auto &b : bullets) {
		window.draw(b);
	}
}

void Bullet::Fire(const sf::Vector2f & pos, const bool mode)
{
	bulletPointer++;
	bullets[bulletPointer].setPosition(pos);
	bullets[bulletPointer]._mode = mode;

	if (mode) {
		bullets[bulletPointer].setPosition(bullets[bulletPointer].getPosition() - Vector2f(0, 32));
		bullets[bulletPointer].setTextureRect(IntRect(32, 32, 32, 32));
	}
	else {
		bullets[bulletPointer].setTextureRect(IntRect(64, 32, 32, 32));
	}
}