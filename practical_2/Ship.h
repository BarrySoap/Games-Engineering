#pragma once
#include <SFML/Graphics.hpp>

class Ship : public sf::Sprite {
protected:
	sf::IntRect _sprite;
	bool _exploded;
	float explosionTime = 0.3f;
	Ship();
public:
	bool is_exploded() const;
	bool shipType;

	explicit Ship(sf::IntRect ir);
	virtual ~Ship() = 0;

	virtual void Update(const float &dt);
	virtual void Explode();
};

class Invader : public Ship {
public:
	Invader(sf::IntRect ir, sf::Vector2f pos);
	Invader();
	static bool direction;
	static float speed;

	virtual void Update(const float &dt);
	void Explode();
};

class Player : public Ship {
public:
	Player();
	void Update(const float &dt) override;
};