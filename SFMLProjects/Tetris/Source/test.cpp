#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Example");
    
    sf::Texture texture1, texture2;
    texture1.loadFromFile("../Assets/TileSheet.png"); // Load your textures
    texture2.loadFromFile("../Assets/TileSheet.png");
    
    sf::Sprite sprite1(texture1), sprite2(texture2);
    
    // Set positions of sprite1 and sprite2
    sprite1.setPosition(100, 100); // Adjust the positions as needed
    sprite1.setOrigin(100, 50); // Adjust the positions as needed
    sprite1.setColor(sf::Color::Red);
    sprite2.setPosition(0, 0);
    std::swap(sprite1, sprite2);

    
    sf::Vector2f distance(152.0f, 152.0f); // Distance vector (x, y)

    sf::Vector2f positionSprite2 = 
        sprite1.getPosition() - sprite1.getOrigin() + distance;

    sprite2.setPosition(positionSprite2);

    sf::VertexArray line(sf::Lines, 2);
    line[0].position = sprite1.getPosition();
    line[1].position = sprite2.getPosition();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite1);
        window.draw(sprite2);
        window.draw(line);
        window.display();
    }

    return 0;
}