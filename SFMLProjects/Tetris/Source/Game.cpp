#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>

void moveDownTileField(std::vector<Tile> &tiles, size_t rowNumber)
{
    for (size_t i = rowNumber; i > 0; i--)
    {
        for (size_t j = 0; j < GameVar::TileColCount; j++)
        {
            std::iter_swap(tiles.begin() + GameVar::TileColCount * i + j, 
                tiles.begin() + GameVar::TileColCount * (i - 1) + j);
            std::swap(tiles[GameVar::TileColCount * i + j], 
                tiles[GameVar::TileColCount * (i - 1) + j]);
            std::cout << "moveDownTileField" << &tiles << '\n';
            //std::cout << "Swapped" << GameVar::TileColCount * i + j << '\n';
            //std::cout << "Swapped" << GameVar::TileColCount * (i - 1) + j << '\n';
            //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
}

bool isRowCompleted(std::vector<Tile> &tiles, size_t rowNumber)
{
    for (size_t i = 0; i < TileColCount; i++)
    {   
        if(!tiles[GameVar::TileColCount * rowNumber + i].isObstackle())
            return false;
    }
    return true;
}

void handleCompletedRow(std::vector<Tile> &tiles)
{
    for (size_t i = 0; i < GameVar::TileRowCount; i++)
        if(isRowCompleted(tiles, i))
        {
            std::cout << "Completed" << '\n';
            for (size_t j = 0; j < GameVar::TileColCount; j++)
            {
                tiles[GameVar::TileColCount * i + j].setIsObstackle(false);
                tiles[GameVar::TileColCount * i + j].setColor(sf::Color::White);
            }
            moveDownTileField(tiles, i);
            std::cout << "handleCompletedRow: "<<&tiles << '\n';
        }
}

int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0); 
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void fillObstackleTiles(std::vector<Tile> &tiles, const Shape &shape)
{
    for(auto &tile: tiles)
    {
        sf::Vector2f tileCenter(tile.getPosition());
        tileCenter.x += GameVar::TileSize / 2;
        tileCenter.y += GameVar::TileSize / 2;

        if(shape.contains(tileCenter))
        {
            tile.setIsObstackle(true);
            tile.setColor(shape.getColor());
        }
    }

}


Game::Game()
{
    win = new sf::RenderWindow
    (
        sf::VideoMode(GameVar::ScreenWidth, GameVar::ScreenHeight),
        "Tetris"
    );
    win->setFramerateLimit(60);

    if(!bgTexture.loadFromFile("../Assets/Background.png"))
        std::cout << "Cant open file\n";
    bgSprite.setTexture(bgTexture);

    if(!tileTexture.loadFromFile("../Assets/TileSheet.png"))
        std::cout << "Cant open file\n";
    tileTexture.setRepeated(true);

    tiles.reserve(GameVar::TileColCount * GameVar::TileRowCount);
    for (size_t i = 0; i < GameVar::TileRowCount; i++)
    {
        for (size_t j = 0; j < GameVar::TileColCount; j++)
        {
            tiles.push_back
            (
                Tile
                (
                    GameVar::Padding + j * GameVar::TileSize, 
                    GameVar::Padding + i * GameVar::TileSize, 
                    GameVar::TileSize
                )
            );
            tiles[i * GameVar::TileColCount + j].setTexture(tileTexture); 
        }
    }
    deltaTime.restart();
    inputDelay.restart();
}

void Game::HandleKeyboard()
{
    static bool SpaceIsHeld = false;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        _isRunning = false;

    if(inputDelay.getElapsedTime().asSeconds() < 0.065)
        return;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        shape.MoveSideway(sf::Keyboard::Left);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        shape.MoveSideway(sf::Keyboard::Right);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        shape.setSpeed(GameVar::ShapeSpeed + 150);

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        shape.setSpeed(GameVar::ShapeSpeed);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !SpaceIsHeld)
    {
        shape.Rotate();
        SpaceIsHeld = true;
    }

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        SpaceIsHeld = false;

    inputDelay.restart();
}

void Game::HandleCollisions()
{
    sf::FloatRect leftScreenBound(0, 0, Padding - 1, ScreenHeight);
    sf::FloatRect rightScreenBound(
        Padding + FieldWidth, 0, ScreenWidth, ScreenHeight);
    sf::FloatRect bottomScreenBound(0, Padding + FieldHeight, 
        ScreenWidth, ScreenHeight);
    if(shape.intersects(leftScreenBound))
    {
        std::cout << "Left intersects" << '\n';
        shape.MoveSideway(sf::Keyboard::Right);

    }
    if(shape.intersects(rightScreenBound))
    {
        std::cout << "Right intersects" << '\n';
        shape.MoveSideway(sf::Keyboard::Left);

    }

    for(auto &tile: tiles)
    {
        if(tile.isObstackle() && 
            shape.intersects(tile.getGloabalBounds()))
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                shape.MoveSideway(sf::Keyboard::Right);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                shape.MoveSideway(sf::Keyboard::Left);
            }
        }
        if(tile.isObstackle() && 
            shape.intersects(tile.getGloabalBounds()))
        {
            shape.setSpeed(0);
            fillObstackleTiles(tiles, shape);
        }
    }

    if(shape.intersects(bottomScreenBound))
    {
        std::cout << "Bottom intersects" << '\n';
        shape.setSpeed(0);
        fillObstackleTiles(tiles, shape);

    }

}

void Game::PollEvent()
{
    sf::Event event;
    while(win->pollEvent(event)){
        switch (event.type)
        {
        case sf::Event::Closed:
            _isRunning = false;
            break;
        default:
            break;
        }
    }
    HandleKeyboard();
}

void Game::Update()
{
    shape.MoveDown(deltaTime.getElapsedTime());
    HandleCollisions();
    handleCompletedRow(tiles);

    if (shape.getSpeed() == 0)
        shape = Shape
        (
            Padding + 4 * TileSize, 
            Padding + 0 * TileSize,
            TileSize, 
            static_cast<ShapeType>(getRandomNumber(0, 6)),
            //ShapeType::Stick,
            tileTexture
        );
    deltaTime.restart();
}

void Game::Render()
{
    win->clear();
    win->draw(bgSprite);
    for(const Tile& tile: tiles)
        win->draw(tile);
    win->draw(shape);
    win->display();
}

bool Game::isRunning()
{
    return _isRunning;
}

Game::~Game()
{
    delete win;
    win = nullptr;
}
