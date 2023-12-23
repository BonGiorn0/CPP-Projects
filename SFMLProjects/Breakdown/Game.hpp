#include <SFML/Graphics.hpp>
#include <vector>

#include "Ball.hpp"
#include "Brick.hpp"
#include "Paddle.hpp"

class Game{
public:
    Game(size_t winHeight, size_t winWidth);
    ~Game();
    bool isRunning();
    void update();
    void render();
    void restart();
    void stop();
private:
    void pollEvent(sf::Event &event);
    void checkCollisions();
    bool running = false; 
    sf::RenderWindow *win = NULL;
    Ball ball;
    Paddle paddle;
    std::vector<Brick> bricks;
    sf::Clock clock;
    sf::Clock deltaTime;

};