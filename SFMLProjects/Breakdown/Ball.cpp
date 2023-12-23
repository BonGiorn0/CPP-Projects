#include <cmath>
#include "Ball.hpp"

Ball::Ball(float x, float y, float radius)
{
    circle.setOrigin(radius, radius);
    circle.setPosition(x, y);
    circle.setRadius(radius);


}

float Ball::getX()
{
    return circle.getPosition().x;
}

float Ball::getY()
{
    return circle.getPosition().y;
}

float Ball::getRadius()
{
    return circle.getRadius();
}

sf::Vector2f Ball::getSpeed() const
{
    return velocity;
}

bool Ball::intersects(const sf::FloatRect &rectangle)
{
    sf::Vector2f tmp = circle.getPosition();

    if(circle.getPosition().x < rectangle.left)
        tmp.x = rectangle.left;
    else if(circle.getPosition().x > rectangle.left + rectangle.width)
        tmp.x = rectangle.left + rectangle.width;

    if(circle.getPosition().y < rectangle.top)
        tmp.y = rectangle.top;
    else if(circle.getPosition().y > rectangle.top + rectangle.height)
        tmp.y = rectangle.top + rectangle.height;

    tmp -= circle.getPosition();
    
    float distance = sqrt(tmp.x * tmp.x + tmp.y * tmp.y);

    return distance < circle.getRadius();
}

void Ball::setSpeed(sf::Vector2f newVelocity)
{
    velocity = newVelocity;
}

void Ball::move(float elapsedTime)
{
    float dx = velocity.x * elapsedTime;
    float dy = velocity.y * elapsedTime;
    circle.move(dx, dy);
}

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(circle);
}
