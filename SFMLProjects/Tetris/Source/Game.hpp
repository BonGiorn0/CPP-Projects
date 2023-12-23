#include <SFML/Graphics.hpp>
#include <vector>

#include "Tile.hpp"
#include "Shape.hpp"

enum GameVar{
    TileSize = 36,
    Padding = TileSize / 2,
    TileRowCount = 20,
    TileColCount = 10,
    FieldWidth = TileSize * TileColCount,
    FieldHeight = TileSize * TileRowCount,
    ScreenWidth = 
        TileSize * TileColCount * 2 + Padding * 2,
    ScreenHeight = 
        TileSize * TileRowCount + Padding * 2,
    ShapeSpeed = 50
};

class Game
{
private:
    void HandleKeyboard();
    void HandleCollisions();
    sf::RenderWindow *win = nullptr;
    std::vector<Tile> tiles;
    sf::Texture tileTexture;
    sf::Texture bgTexture;
    sf::Sprite bgSprite;
    Shape shape;
    sf::Clock inputDelay;
    sf::Clock deltaTime;
    bool _isRunning = true;
public:
    Game(/* args */);
    void PollEvent();
    void Update();
    void Render();
    bool isRunning();
    ~Game();
};
