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
const float ballRadius = 10.0f;				// Size of ball / 2
const int gameWidth = 800;					// Screen Width
const int gameHeight = 600;					// Screen Height
const float paddleSpeed = 400.0f;			// Paddle movement speed

CircleShape ball;							// Ball object
RectangleShape paddles[2];					// Container for paddles

void Load() {
	// Set size and origin of paddles
	for (auto &paddle : paddles) {
		paddle.setSize(paddleSize - Vector2f(3, 3));
		paddle.setOrigin(paddleSize / 2.0f);
	}
	// Set size and origin of ball
	ball.setRadius(ballRadius - 3);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);
	// Reset paddle position
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition(gameWidth - (10 + paddleSize.x / 2), gameHeight / 2);
	// Reset ball position
	ball.setPosition(gameWidth / 2, gameHeight / 2);
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

	// Handle paddle movement
	float direction = 0.0f;
	if (Keyboard::isKeyPressed(controls[0])) {
		direction--;
	}
	if (Keyboard::isKeyPressed(controls[1])) {
		direction++;
	}
	paddles[0].move(0, direction * paddleSpeed * dt);
}

void Render(RenderWindow &window) {
	// Draw everything
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}