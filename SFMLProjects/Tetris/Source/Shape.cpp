#include "Shape.hpp"
#include <iostream>

Shape::Shape(float x, float y, float size, 
    ShapeType shapeType, sf::Texture &texture)
    : tileSize(size)
{
    sf::Sprite sprite(texture);
    unsigned int textureSize = texture.getSize().y - 1;
    sprite.setScale
    (
        tileSize / (textureSize + 1), 
        tileSize / (textureSize + 1)
    );

    rectangles.push_back(sprite);
    switch(shapeType)
    {
    case ShapeType::LShape:
        rectangles.push_back(sprite);
        rectangles[0].setPosition(x + 1.5f * tileSize, y + tileSize);
        rectangles[1].setPosition(x + 1.5f * tileSize, y + tileSize);
        rectangles[0].setTextureRect(
            sf::IntRect(0, 0, textureSize, 3 * textureSize));
        rectangles[1].setTextureRect(
            sf::IntRect(0, 0, textureSize, textureSize));
        rectangles[0].setOrigin(
            0.5f * textureSize, 1.5f * textureSize);
        rectangles[1].setOrigin(
            1.5f * textureSize, 1.5f * textureSize);
        break;
    case ShapeType::MirroredLShape:
        rectangles.push_back(sprite);
        rectangles[0].setPosition(x + 1.5f * tileSize, y + tileSize);
        rectangles[1].setPosition(x + 1.5f * tileSize, y + tileSize);
        rectangles[0].setTextureRect(
            sf::IntRect(0, 0, 3 * textureSize, textureSize));
        rectangles[1].setTextureRect(
            sf::IntRect(0, 0, textureSize, textureSize));
        rectangles[0].setOrigin(
            1.5f * textureSize, 0.5f * textureSize);
        rectangles[1].setOrigin(
            1.5f * textureSize, 1.5f * textureSize);
        break;
    case ShapeType::TShape:
        rectangles.push_back(sprite);
        rectangles[0].setPosition(x + 1.5f * tileSize, y + tileSize);
        rectangles[1].setPosition(x + 1.5f * tileSize, y + tileSize);
        rectangles[0].setTextureRect(
            sf::IntRect(0, 0, 3 * textureSize, textureSize));
        rectangles[1].setTextureRect(
            sf::IntRect(0, 0, textureSize, textureSize));
        rectangles[0].setOrigin(
            1.5f * textureSize, 0.5f * textureSize);
        rectangles[1].setOrigin(
            0.5f * textureSize, 1.5f * textureSize);
        break;
    case ShapeType::ZShape:
        rectangles.push_back(sprite);
        rectangles[0].setPosition(x + 1.5f * tileSize, y + tileSize);
        rectangles[1].setPosition(x + 1.5f * tileSize, y + tileSize);
        rectangles[0].setTextureRect(
            sf::IntRect(0, 0, 2 * textureSize, textureSize - 1));
        rectangles[1].setTextureRect(
            sf::IntRect(0, 0, 2 * textureSize, textureSize - 1));
        rectangles[1].setOrigin(
            0.5f * textureSize, 0.5f * textureSize);
        rectangles[0].setOrigin(
            1.5f * textureSize, 1.5f * textureSize);
        break;
    case ShapeType::MirroredZShape:
        rectangles.push_back(sprite);
        rectangles[0].setPosition(x + 1.5f * tileSize, y + tileSize);
        rectangles[1].setPosition(x + 1.5f * tileSize, y + tileSize);
        rectangles[0].setTextureRect(
            sf::IntRect(0, 0, 2 * textureSize, textureSize));
        rectangles[1].setTextureRect(
            sf::IntRect(0, 0, 2 * textureSize, textureSize));
        rectangles[0].setOrigin(
            1.5f * textureSize, 0.5f * textureSize);
        rectangles[1].setOrigin(
            0.5f * textureSize, 1.5f * textureSize);
        break;
    case ShapeType::Square:
        rectangles[0].setPosition(x + 1.0f * tileSize, y + tileSize);
        rectangles[0].setTextureRect
        (
            sf::IntRect(0, 0, 
                        2 * textureSize, 
                        2 * textureSize)
        );
        rectangles[0].setOrigin(textureSize, textureSize);
        break;
    case ShapeType::Stick:
        rectangles[0].setPosition(x + 1.5f * tileSize, y + tileSize);
        rectangles[0].setTextureRect(
            sf::IntRect(0, 0, 
                4 * textureSize, 
                1 * textureSize)
        );
        rectangles[0].setOrigin(
            1.5f * textureSize, 0.5f * textureSize);
        break;
    };
    for(auto &rect: rectangles)
        ;
    rectangles[0].setColor(sf::Color::Red);
    rectangles[1].setColor(sf::Color::Green);
}

void Shape::MoveDown(sf::Time elapsedTime)
{
    for (auto &rect : rectangles)
        rect.move(0, speed * elapsedTime.asSeconds());

}

void Shape::MoveSideway(sf::Keyboard::Key key)
{
    int direction = (key == sf::Keyboard::Left) ? -1 : 1;
    for (auto &rect : rectangles)
        rect.move(direction * tileSize, 0);
    std::cout << rectangles[0].getPosition().x <<'\n';
}

void Shape::setSpeed(float newSpeed)
{
    speed = newSpeed;
}

float Shape::getSpeed() const
{
    return speed;
}

sf::Color Shape::getColor() const
{
    return rectangles[0].getColor();
}

void Shape::Rotate()
{
    for (auto &rect : rectangles)
        rect.rotate(90);
}

bool Shape::intersects(sf::FloatRect otherRect) const
{
    for(const auto& rect : rectangles)
        if(rect.getGlobalBounds().intersects(otherRect))
            return true;

    return false;
}

bool Shape::contains(sf::Vector2f &point) const
{
    for(const auto& rect : rectangles)
        if(rect.getGlobalBounds().contains(point)) 
            return true;

    return false;
}

void Shape::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(const auto& rect : rectangles)
        target.draw(rect);
    /*for(const auto& rect : rectangles)
    {
        sf::Vector2f size(
            rect.getGlobalBounds().width,rect.getGlobalBounds().height);
        sf::Vector2f pos(
            rect.getGlobalBounds().left,rect.getGlobalBounds().top);
        sf::RectangleShape bounds(size);
        bounds.setPosition(pos);
        bounds.setFillColor(sf::Color(0,0,0,0));
        bounds.setOutlineThickness(-3);
        bounds.setOutlineColor(sf::Color::Cyan);
        target.draw(bounds);

    }*/

}
