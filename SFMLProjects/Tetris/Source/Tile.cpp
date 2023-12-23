#include "Tile.hpp"
#include <iostream>
#include <algorithm>

Tile::Tile(float x, float y, float size)
{
    sprite.setPosition(x, y);
    tileSize = size;
}

Tile::Tile(const Tile &other)
{
    sprite = sf::Sprite(other.sprite);
    tileSize = other.tileSize;
    obstackleState = other.obstackleState;
}

/*Tile::Tile(Tile &&other)
{
    std::swap(obstackleState, other.obstackleState);
    std::swap(sprite, other.sprite);
    std::swap(tileSize, other.tileSize);
}*/


Tile &Tile::operator=(const Tile &other)
{
    sprite = sf::Sprite(other.sprite);
    tileSize = other.tileSize;
    obstackleState = other.obstackleState;
    return *this;
}

/*Tile &Tile::operator=(Tile &&other)
{
    std::swap(obstackleState, other.obstackleState);
    std::swap(sprite, other.sprite);
    std::swap(tileSize, other.tileSize);
    return *this;
}*/

void Tile::setTexture(sf::Texture &texture)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 
        texture.getSize().y, texture.getSize().y));
    sprite.setColor(sf::Color(255, 255, 255, 255));
    sprite.setScale
    (
        tileSize / texture.getSize().y, 
        tileSize / texture.getSize().y
    );
}

void Tile::setIsObstackle(bool state)
{
    obstackleState = state;
}

void Tile::setColor(sf::Color color)
{
    sprite.setColor(color);
}

sf::Vector2f Tile::getPosition() const
{
    return sprite.getPosition();
}

sf::FloatRect Tile::getGloabalBounds() const
{
    return sprite.getGlobalBounds();
}

bool Tile::isObstackle()
{
    return obstackleState;
}

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite);
}
