#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
	Keyboard::W,	// Player1 UP
	Keyboard::S,	// Player1 DOWN
	Keyboard::Up,	// Player2 UP
	Keyboard::Down	// Player2 DOWN
};

const Vector2f paddleSize(25.0f, 100.0f);
const float ballRadius = 10.0f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.0f;

CircleShape ball;
RectangleShape paddles[2];

void Load() {
	// Set size and origin of paddles
	for (auto &paddle : paddles) {
		paddle.setSize(paddleSize - Vector2f(3, 3));
		paddle.setOrigin(paddleSize / 2.0f);
	}
	// Set size and origin of ball
	ball.setRadius(ballRadius - 3);
	ball.setOrigin(ballRadius - Vector2f(3, 3));
}