#include "Paddle.hpp"

#include <iostream>

Paddle::Paddle(float x, float y, float width, float height)
{
    rectangle.setPosition(x, y);
    rectangle.setSize(sf::Vector2f(width, height));
    rectangle.setOrigin(width / 2, 0);
    prevPosition = currPosition = width / 2;
}

float Paddle::getX() const
{
    return rectangle.getPosition().x;
}

float Paddle::getY() const
{
    return rectangle.getPosition().y;
}

float Paddle::getWidth() const
{
    return rectangle.getSize().x;
}

float Paddle::getHeight() const
{
    return rectangle.getSize().y;
}

float Paddle::getSpeed()
{
    sf::Time elapsedTime = clock.getElapsedTime();
    return (prevPosition - currPosition) / elapsedTime.asSeconds();
}

sf::FloatRect Paddle::getGlobalBounds()
{
    return rectangle.getGlobalBounds();
}

void Paddle::setX(float x)
{
    float y = rectangle.getPosition().y;
    rectangle.setPosition(sf::Vector2f(x, y));
}

void Paddle::updatePrevPosition()
{
    if(clock.getElapsedTime().asSeconds() > 0.1f){
        prevPosition = currPosition;
        currPosition = getX();
        clock.restart();
    }

    //std::cout << prevPosition << ';' << currPosition << '\n';
    //std::cout << clock.getElapsedTime().asSeconds() << '\n';
    
}

void Paddle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(rectangle);
}
