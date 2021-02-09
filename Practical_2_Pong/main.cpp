#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const Keyboard::Key controls[5] =
{
	Keyboard::A,   // Player1 UP
	Keyboard::Z,   // Player1 Down
	Keyboard::K,  // Player 2 UP
	Keyboard::M, // Player 2 Down
	Keyboard::P // Enable 2 Players
};

const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 500.f;

Vector2f ballVelocity;
bool server = false;
bool twoPlayersMode = false;
sf::Font font;
sf::Text scoreTextLeft;
sf::RectangleShape net;
int scoreLeft = 0;
sf::Text scoreTextRigth;
sf::Text playerMode;
int scoreRight = 0;
const Vector2f paddleSize(25.f, 100.f);
const Vector2f netSize(1.f, gameHeight);

CircleShape ball;
RectangleShape paddles[2];

void Load() {
	// Set net size and position
	net.setSize(sf::Vector2f(1.f, gameHeight));
	net.setPosition(sf::Vector2f(gameWidth / 2, 1));
	//Set size and origin of paddles
	for (auto& p : paddles) {
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize / 3.f);
	}

	// Set size and origin of ball
	ball.setRadius(ballRadius - 3);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);
	// Reset paddle position
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition(760 + paddleSize.x / 2, gameHeight / 2);
	// Reset Ball Position
	ball.setPosition(gameWidth / 2, gameHeight / 2);

	// This will set the direction of the ball either
	// to the left or to the right when the game starts
	ballVelocity = { (server ? 200.0f : -200.0f), 40.0f };

	//Load font-face from res direction
	font.loadFromFile("res/Fira.otf");
	// Set text element to use font
	scoreTextLeft.setFont(font);
	scoreTextRigth.setFont(font);
	playerMode.setFont(font);
	// Set the character size to 24 pixels
	scoreTextLeft.setCharacterSize(24);
	scoreTextRigth.setCharacterSize(24);
	playerMode.setCharacterSize(16);
	// Set the string text
	scoreTextLeft.setString("0");
	scoreTextRigth.setString("0");
	playerMode.setString("AI Mode");
	// Set text color
	scoreTextLeft.setFillColor(sf::Color::White);
	scoreTextRigth.setFillColor(sf::Color::White);
	playerMode.setFillColor(sf::Color::White);
	// Set text position
	scoreTextLeft.setPosition((gameWidth * .5f / 2) - (scoreTextLeft.getLocalBounds().width * .5f), 0);
	scoreTextRigth.setPosition((gameWidth * .5f + gameWidth * .5f / 2) - (scoreTextRigth.getLocalBounds().width * .5f), 0);
	playerMode.setPosition(10, 0);
}

void Reset() {
	// Reset paddle position
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition(760 + paddleSize.x / 2, gameHeight / 2);
	// Reset Ball Position
	ball.setPosition(gameWidth / 2, gameHeight / 2);
	// Reset Ball Speed
	ballVelocity = { (server ? 200.0f : -200.0f), 40.0f };
	// Update Score Text
	//scoreText.setString("1");
	// Keet Score Text centered
	scoreTextLeft.setPosition((gameWidth * .5f / 2) - (scoreTextLeft.getLocalBounds().width * .5f), 0);
	scoreTextLeft.setString(to_string(scoreLeft));
	scoreTextRigth.setPosition((gameWidth * .5f + gameWidth * .5f / 2) - (scoreTextRigth.getLocalBounds().width * .5f), 0);
	scoreTextRigth.setString(to_string(scoreRight));
}

void Update(RenderWindow& window) {
	// Get ball position
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;
	// Reset clock, recalculate deltatime
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
	float direction2 = 0.0f;
	if (Keyboard::isKeyPressed(controls[0]) && paddles[0].getPosition().y > 35) {
		direction--;
	}
	if (Keyboard::isKeyPressed(controls[1]) && paddles[0].getPosition().y < gameHeight - 65) {
		direction++;
	}

	if (event.key.code == sf::Keyboard::P) {
		twoPlayersMode = { (twoPlayersMode ? false : true) };
	}

	if (twoPlayersMode == false) {
		playerMode.setString("AI Mode");
	}

	else if (twoPlayersMode == true) {
		playerMode.setString("2 Players Mode");
	}

	// Enables second player to move the right paddle if twoPlayersMode is enable
	if (Keyboard::isKeyPressed(controls[2]) && paddles[1].getPosition().y > 35 && twoPlayersMode == true) {
		direction2--;
	}
	if (Keyboard::isKeyPressed(controls[3]) && paddles[1].getPosition().y < gameHeight - 65 && twoPlayersMode == true) {
		direction2++;
	}

	// Enables AI to play as the right player if twoPlayersMode is disabled
	if (paddles[1].getPosition().y > 35 && paddles[1].getPosition().y + paddleSize.y / 2 > by && bx > gameWidth / 2 && twoPlayersMode == false) {
		direction2--;
	}
	if (paddles[1].getPosition().y < gameHeight - 65 && paddles[1].getPosition().y + paddleSize.y / 2 < by && bx > gameWidth / 2 && twoPlayersMode == false) {
		direction2++;
	}

	paddles[0].move(0, direction * paddleSpeed * dt);
	paddles[1].move(0, direction2 * paddleSpeed * dt);

	ball.move(ballVelocity * dt);

	// Check ball collision
	if (by > gameHeight - 10) {
		// Bottom wall
		ballVelocity.x *= 1.05f;
		ballVelocity.y *= -1.05f;
		ball.move(0, -5);
	}
	else if (by < 10) {
		// Top wall
		ballVelocity.x *= 1.05f;
		ballVelocity.y *= -1.05f;
		ball.move(0, 5);
	}

	// Ball is inline or behind paddle and ball is below top edge of paddle and ball is above bottom edge of paddle
	else if (bx < paddleSize.x + 15 && by > paddles[0].getPosition().y - (paddleSize.y * 0.40) && by < paddles[0].getPosition().y + (paddleSize.y * 0.60)) {
		// Bounce off left paddle
		ballVelocity.x *= -1.05f;
		ballVelocity.y *= 1.05f;
		ball.move(10, 0);
	}

	// Ball is inline or behind paddle and ball is below top edge of paddle and ball is above bottom edge of paddle
	else if (bx > paddleSize.x + 735 && by > paddles[1].getPosition().y - (paddleSize.y * 0.40) && by < paddles[1].getPosition().y + (paddleSize.y * 0.60)) {
		// Bounce off right paddle
		ballVelocity.x *= -1.05f;
		ballVelocity.y *= 1.05f;
		ball.move(-10, 0);
	}

	else if (bx > gameWidth) {
		server = true;
		scoreLeft++;
		Reset();
	}
	else if (bx < 0) {
		server = false;
		scoreRight++;
		Reset();
	}
}

void Render(RenderWindow& window) {
	// Draw Everything
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
	window.draw(scoreTextLeft);
	window.draw(scoreTextRigth);
	window.draw(playerMode);
	window.draw(net);
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