#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const Keyboard::Key controls[5] = {
    Keyboard::A,   // Player1 Left
    Keyboard::D,   // Player1 Right
};

const int gameWidth = 800;
const int gameHeight = 600;

void Load() {

}

void Update(RenderWindow& window){

}

void Render(RenderWindow& window) {

}
int main()
{
    RenderWindow window(VideoMode(gameWidth, gameHeight), "Space Invaders");
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