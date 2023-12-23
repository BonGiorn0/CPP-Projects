#include "Game.hpp"

#include <iostream>

float paddleWidth = 250;
float paddleHeight = 30;
float ballRadius = 15;
int bricksInRowCount = 11;
int bricksInColCount = 5;

Game::Game(size_t winWidth, size_t winHeight)
{
    win = new sf::RenderWindow(sf::VideoMode(winWidth, winHeight), "Breakdown");
    win->setSize(sf::Vector2u(winWidth, winHeight));
    win->setFramerateLimit(60);

    ball = Ball(winWidth / 2, winHeight - 250, ballRadius);
    paddle = Paddle(0, winHeight - paddleHeight - 15, paddleWidth, paddleHeight);

    bricks.reserve(bricksInRowCount * bricksInColCount);
    for (size_t i = 0; i < bricksInColCount; i++)
        for (size_t j = 0; j < bricksInRowCount; j++)
            bricks.push_back(Brick(2 + 5 * (j + 1) + 101 * j, 7 * (i + 1) + 60 * i, 100, 60));

    running = true;
}

bool Game::isRunning()
{
    return running;
}

void Game::render()
{
    win->clear();
    win->draw(ball);
    win->draw(paddle);
    for (auto i = bricks.begin(); i != bricks.end(); i++)
            win->draw(*i);
    win->display();
}

void Game::restart()
{
    ball = Ball(win->getSize().x / 2, win->getSize().y - 250, ballRadius);
    paddle = Paddle(0, win->getSize().y - paddleHeight - 15, paddleWidth, paddleHeight);

    bricks.clear();
    bricks.reserve(bricksInRowCount * bricksInColCount);
    for (size_t i = 0; i < bricksInColCount; i++)
        for (size_t j = 0; j < bricksInRowCount; j++)
            bricks.push_back(Brick(2 + 7 * (j + 1) + 101 * j, 7 * (i + 1) + 60 * i, 100, 60));

    clock.restart();

}

void Game::update()
{
    sf::Event event;
    while(win->pollEvent(event)){
        this->pollEvent(event);
    }
    paddle.updatePrevPosition();
    checkCollisions();
    //if(clock.getElapsedTime().asSeconds() > 3.0f)
        ball.move(deltaTime.getElapsedTime().asSeconds());
    deltaTime.restart();
}

void Game::pollEvent(sf::Event &event)
{
    sf::Vector2i pos;
    sf::Vector2f localPos;
    switch(event.type){
    case sf::Event::Closed:
        stop();
        break;
    case sf::Event::KeyPressed:
        if(event.key.code == sf::Keyboard::Escape)
            stop();
        break;
    case sf::Event::MouseMoved:
        pos = sf::Mouse::getPosition(*win);
        localPos = win->mapPixelToCoords(pos);
        if(localPos.x < paddle.getWidth() / 2)
            localPos.x = paddle.getWidth() / 2;
        if(localPos.x > win->getSize().x - paddle.getWidth() / 2)
            localPos.x = win->getSize().x - paddle.getWidth() / 2;
        paddle.setX(localPos.x);
        break;
    default:
        break;
    }
}

void Game::checkCollisions()
{
    //left and right sides collision
    if(ball.getX() < ball.getRadius() ||
        win->getSize().x - ball.getX() < ball.getRadius())
    {
        sf:: Vector2f newSpeed = ball.getSpeed();
        newSpeed.x = -newSpeed.x;
        ball.setSpeed(newSpeed);
    }

    //top collision
    if(ball.getY() < ball.getRadius()) 
    {
        sf:: Vector2f newSpeed = ball.getSpeed();
        newSpeed.y = -newSpeed.y;
        ball.setSpeed(newSpeed);
    }

    //bottom collision
    if(win->getSize().y - ball.getY() < ball.getRadius())
    {
        restart();
    }
    

    //paddle collision
    if(ball.intersects(paddle.getGlobalBounds()))
    {
        if((ball.getX() < paddle.getX() + paddle.getWidth() / 2 &&
            ball.getX() > paddle.getX() - paddle.getWidth() / 2) &&
            ball.getSpeed().y > 0) 
        {
            sf:: Vector2f newSpeed = ball.getSpeed();
            newSpeed.y = -newSpeed.y;
            ball.setSpeed(newSpeed);
        }
        else if(ball.getY() > paddle.getY() &&
            ball.getSpeed().y > 0) 
        {
            sf:: Vector2f newSpeed = ball.getSpeed();
            newSpeed.x = -newSpeed.x;
            ball.setSpeed(newSpeed);
        }
        else if(ball.getSpeed().y > 0)
        {
            sf:: Vector2f newSpeed = ball.getSpeed();
            newSpeed.y = -newSpeed.y;
            newSpeed.x = -newSpeed.x;
            ball.setSpeed(newSpeed);

        }
    }

    //bricks collision
    for (auto it = bricks.begin(); it != bricks.end();)
    {
        if(ball.intersects(it->getGlobalBounds()))
        {
            if((ball.getX() < it->getX() || 
                ball.getX() > it->getX() + it->getWidth()))
            {
                sf:: Vector2f newSpeed = ball.getSpeed();
                newSpeed.x = -newSpeed.x;
                ball.setSpeed(newSpeed);
            }
            if(ball.getY() < it->getY() || 
                ball.getY() > it->getY() + it->getHeight())
            {
                sf:: Vector2f newSpeed = ball.getSpeed();
                newSpeed.y = -newSpeed.y;
                ball.setSpeed(newSpeed);
            }
            if(false)
            {
                sf:: Vector2f newSpeed = ball.getSpeed();
                newSpeed.y = -newSpeed.y;
                newSpeed.x = -newSpeed.x;
                ball.setSpeed(newSpeed);
            }
            it = bricks.erase(it);
        }
        else
        {
            it++;
        }
    }

}

void Game::stop()
{
    this->~Game();
}

Game::~Game()
{
    running = false;
    delete win;
    win = NULL;
}
