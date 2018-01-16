#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] =
{
	Keyboard::W,	// Player1 UP
	Keyboard::S,	// Player1 DOWN
	Keyboard::Up,	// Player2 UP
	Keyboard::Down	// Player2 DOWN
};

const Vector2f paddleSize(25.0f, 100.0f);
Vector2f ballVelocity;						// Velocity of the ball (speed + direction)
const float ballRadius = 10.0f;				// Size of ball / 2
const int gameWidth = 800;					// Screen Width
const int gameHeight = 600;					// Screen Height
const float paddleSpeed = 400.0f;			// Paddle movement speed
bool server = false;

CircleShape ball;							// Ball object
RectangleShape paddles[2];					// Container for paddles

Font font;
Text text;

void reset()
{
	// Reset paddle position
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition(gameWidth - (10 + paddleSize.x / 2), gameHeight / 2);
	// Reset ball position
	ball.setPosition(gameWidth / 2, gameHeight / 2);

	// Update Score Text
	text.setString("0");
	// Keep Score Text Centred
	text.setPosition((gameWidth * 0.5f) - (text.getLocalBounds().width * 0.5f), 0);
}

void Load()
{
	// Set size and origin of paddles
	for (auto &paddle : paddles)
	{
		paddle.setSize(paddleSize - Vector2f(3, 3));
		paddle.setOrigin(paddleSize / 2.0f);
	}
	// Set size and origin of ball
	ball.setRadius(ballRadius - 3);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);
	// Set initial paddle and ball position
	reset();
	// Set ball velocity
	// If server = true, vel = -100.0f, if false, vel = 60.0f
	ballVelocity = { server ? 100.0f : -100.0f, 60.0f };
	// Load score fonts
	font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");
	// Set text element to use font
	text.setFont(font);
	// Set the character size to 24 pixels
	text.setCharacterSize(24);
}

void Update(RenderWindow &window)
{
	// Reset clock, recalculate deltaTime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	// Check and consume events
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
			return;
		}
	}

	// Quit via ESC key
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		window.close();
	}

	// Handle paddle movement
	float leftDirection = 0.0f;
	float rightDirection = 0.0f;
	if (Keyboard::isKeyPressed(controls[0]))
	{
		leftDirection--;
	}
	if (Keyboard::isKeyPressed(controls[1]))
	{
		leftDirection++;
	}
	if (Keyboard::isKeyPressed(controls[2]))
	{
		rightDirection--;
	}
	if (Keyboard::isKeyPressed(controls[3]))
	{
		rightDirection++;
	}
	paddles[0].move(0, leftDirection * paddleSpeed * dt);
	paddles[1].move(0, rightDirection * paddleSpeed * dt);
	ball.move(ballVelocity * dt);

	// Check ball collision
	const float bx = ball.getPosition().x;		// Ball x position
	const float by = ball.getPosition().y;		// Ball y position
	if (by > gameHeight)
	{
		// Bottom wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, -10);
	}
	else if (by < 0)
	{
		// Top wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, 10);
	}
	else if (bx > gameWidth)
	{
		// Right wall
		reset();
	}
	else if (bx < 0)
	{
		// Left wall
		reset();
	}
	else if (
		// Ball is inline or behind left paddle
		bx < paddleSize.x &&
		// AND ball is below top edge of paddle
		by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
		// AND ball is above bottom edge of paddle
		by < paddles[0].getPosition().y + (paddleSize.y * 0.5)
		) {
		// Bounce off left paddle
		ballVelocity *= -1.1f;
	}
	else if (
		// Ball is inline or right behind paddle
		bx > paddles[1].getPosition().x - (paddleSize.x * 0.5) &&
		// AND ball is below top edge of paddle
		by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&
		// AND ball is above bottom edge of paddle
		by < paddles[1].getPosition().y + (paddleSize.y * 0.5)
		) {
		// Bounce off left paddle
		ballVelocity *= -1.1f;
	}

	// Check paddle collision
	if (paddles[0].getPosition().y + paddleSize.y / 2 > gameHeight) 
	{
		paddles[0].setPosition(paddles[0].getPosition().x, gameHeight - paddleSize.y / 2);
	}
	else if (paddles[0].getPosition().y - paddleSize.y / 2 < 0) 
	{
		paddles[0].setPosition(paddles[0].getPosition().x, 0 + paddleSize.y / 2);
	}
	else if (paddles[1].getPosition().y + paddleSize.y / 2 > gameHeight) 
	{
		paddles[1].setPosition(paddles[1].getPosition().x, gameHeight - paddleSize.y / 2);
	}
	else if (paddles[1].getPosition().y - paddleSize.y / 2 < 0)
	{
		paddles[1].setPosition(paddles[1].getPosition().x, 0 + paddleSize.y / 2);
	}

	// Basic AI
	paddles[1].setPosition(paddles[1].getPosition().x, ball.getPosition().y);
}

void Render(RenderWindow &window)
{
	// Draw everything
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
	window.draw(text);
}

int main()
{
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Pong Game");
	Load();
	while (window.isOpen())
	{
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}