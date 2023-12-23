#include <iostream>
#include "Brick.hpp"

size_t Brick::objCount = 0;

Brick::Brick(float x, float y, float width, float height)
{
    rectangle.setPosition(x, y);
    rectangle.setSize(sf::Vector2f(width, height));
    objCount++;

    std::cout << "Brick created: " << objCount << '\n';
}

Brick::Brick(const Brick &other)
{
    rectangle.setPosition(other.rectangle.getPosition());
    rectangle.setSize(other.rectangle.getSize());
}

Brick::~Brick()
{
    std::cout << "Brick deleted: " <<  objCount << '\n';
    objCount--;
}

float Brick::getX()
{
    return rectangle.getPosition().x;
}

float Brick::getY()
{
    return rectangle.getPosition().y;
}

float Brick::getWidth()
{
    return rectangle.getSize().x;
}

float Brick::getHeight()
{
    return rectangle.getSize().y;
}

sf::FloatRect Brick::getGlobalBounds()
{
    return rectangle.getGlobalBounds();
}

void Brick::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(rectangle);
}
