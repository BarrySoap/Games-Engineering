#include <iostream>
#include "Ship.h"
#include "game.h"
#include "bullet.h"

using namespace sf;
using namespace std;

Ship::Ship() {};

Ship::~Ship() = default;

Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
	_exploded = false;
};

void Ship::Update(const float &dt) {
	if (_exploded) {
		explosionTime -= dt;
	}
	if (explosionTime <= 0.0f) {
		setColor(Color(0, 0, 0, 0));
	}
}

void Ship::Explode() {
	_exploded = true;
}

bool Ship::is_exploded() const {
	return _exploded;
}

bool Invader::direction;
float Invader::speed;

Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
}

void Invader::Explode() {
	Ship::Explode();
	setTextureRect(IntRect(128, 32, 32, 32));
}

void Invader::Update(const float &dt) {
	static float firetime = 0.0f;
	firetime -= dt;

	Ship::Update(dt);

	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

	if ((direction && getPosition().x > gameWidth - 16) ||
		!direction && getPosition().x < 16) {
		direction = !direction;

		for (int i = 0; i < ships.size(); i++) 
		{
			if (ships[i]->shipType == false) 
			{
				ships[i]->move(0, 24);
			}
		}
	}

	if (firetime <= 0 && rand() % 100 == 0) {
		Bullet::Fire(getPosition(), true);
		firetime = 4.0f + (rand() % 60);
	}
}

Player::Player() : Ship(IntRect(160, 32, 32, 32)) {
	setPosition({ gameHeight * .5f, gameHeight - 32.f });
}

void Player::Update(const float &dt) {
	Ship::Update(dt);

	static vector<Bullet *> bullets;
	static float firetime = 0.0f;
	firetime -= dt;
	float direction = 0.0f;

	// Move left
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		direction--;
		Ship::move(direction * shipSpeed * dt, 0);
	}
	// Move right
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		direction++;
		Ship::move(direction * shipSpeed * dt, 0);
	}

	if (firetime <= 0 && Keyboard::isKeyPressed(Keyboard::Space)) 
	{
		bullets.push_back(new Bullet(getPosition(), false));
	}

	if (firetime <= 0 && Keyboard::isKeyPressed(Keyboard::Space)) {
		Bullet::Fire(getPosition(), false);
		firetime = 0.5f;
	}

	for (const auto s : bullets)
	{
		s->Update(dt);
	}
}