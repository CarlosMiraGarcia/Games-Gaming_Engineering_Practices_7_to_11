#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = 
{
    Keyboard::A,   // Player1 UP
    Keyboard::Z,   // Player1 Down
    Keyboard::K,  // Player 2 UP
    Keyboard::M // Player 2 Down
};

const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 500.f;
Vector2f ballVelocity;
bool server = false;

CircleShape ball;
RectangleShape paddles[2];

void Load()
{
    //Set size and origin of paddles
    for (auto &p : paddles)
    {
        p.setSize(paddleSize - Vector2f(3, 3));
        p.setOrigin(paddleSize / 3.f);
    }

    // Set size and origin of ball
    ball.setRadius(ballRadius - 3);
    ball.setOrigin(ballRadius / 2, ballRadius / 2);
    // Reset paddle position
    paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
    paddles[1].setPosition(760 + paddleSize.x / 2, gameHeight /2);
    // Reset Ball Position
    ball.setPosition(gameWidth / 2, gameHeight /2);

    // This will set the direction of the ball either
    // to the left or to the right when the game starts
    ballVelocity = {(server ? 100.0f : -100.0f), 220.0f};
}

void Reset()
{
    // Reset paddle position
    paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
    paddles[1].setPosition(760 + paddleSize.x / 2, gameHeight / 2);
    // Reset Ball Position
    ball.setPosition(gameWidth / 2, gameHeight / 2);
    // Reset Ball Speed
    ballVelocity = { (server ? 100.0f : -100.0f), 220.0f };

}

void Update(RenderWindow& window)
{
    // Reset clock, recalculate deltatime
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
    float direction = 0.0f;
    float direction2 = 0.0f;
    if (Keyboard::isKeyPressed(controls[0]))
    {
        direction--;
    }
    if (Keyboard::isKeyPressed(controls[1]))
    {
        direction++;
    }    
    if (Keyboard::isKeyPressed(controls[2]))
    {
        direction2--;
    }
    if (Keyboard::isKeyPressed(controls[3]))
    {
        direction2++;
    }
    paddles[0].move(0, direction * paddleSpeed * dt);
    paddles[1].move(0, direction2 * paddleSpeed * dt);

    ball.move(ballVelocity * dt);

    // Check ball collision
    const float bx = ball.getPosition().x;
    const float by = ball.getPosition().y;
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

    // Ball is inline or behind paddle and ball is below top edge of paddle and ball is above bottom edge of paddle
    else if (bx < paddleSize.x + 15 && by > paddles[0].getPosition().y - (paddleSize.y * 0.5) && by < paddles[0].getPosition().y + (paddleSize.y * 0.5))
    {
        // Bounce off right paddle
        ballVelocity.x *= -1.1f;
        ballVelocity.y *= 1.1f;
        ball.move(10, 0);
    }

    // Ball is inline or behind paddle and ball is below top edge of paddle and ball is above bottom edge of paddle
    else if (bx > paddleSize.x + 735 && by > paddles[1].getPosition().y - (paddleSize.y * 0.5) && by < paddles[1].getPosition().y + (paddleSize.y * 0.5))
    {
        // Bounce off left paddle
        ballVelocity.x *= -1.1f;
        ballVelocity.y *= 1.1f;
        ball.move(-10, 0);
    }

    else if (bx > gameWidth)
    {
        server = true;
        Reset();
    }
    else if (bx < 0)
    {
        server = false;
        Reset();
    }
}


void Render(RenderWindow &window)
{
    // Draw Everything
    window.draw(paddles[0]);
    window.draw(paddles[1]);
    window.draw(ball);
}

int main()
{
    RenderWindow window (VideoMode(gameWidth, gameHeight), "PONG");
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

