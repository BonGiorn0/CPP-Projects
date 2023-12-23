#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(700, 700), "SFML works!");
    window.setFramerateLimit(60);

    sf::RectangleShape shape(sf::Vector2f(600.f, 600.f));
    shape.setPosition(350 - 300, 350 - 300);
    sf::Texture texture;
    texture.loadFromFile("chess.png");
    texture.setRepeated(true);
    shape.setTexture(&texture);
    //shape.setFillColor(sf::Color(255, 128, 39, 255));
    shape.setOutlineThickness(50.f);
    shape.setOutlineColor(sf::Color(150, 150, 100));


    while (window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                //if (event.key.code == sf::Keyboard::Escape)
                //{ 
                    std::cout << "code:"<< event.key.code << std::endl;
                    std::cout << "control:" << event.key.control << std::endl;
                    std::cout << "alt:" << event.key.alt << std::endl;
                    std::cout << "shift:" << event.key.shift << std::endl;
                    std::cout << "system:" << event.key.system << std::endl;
                //}
            }
            if (event.type == sf::Event::JoystickButtonPressed)
            {
                std::cout << "joystick button pressed!" << std::endl;
                std::cout << "joystick id: " << event.joystickButton.joystickId << std::endl;
                std::cout << "button: " << event.joystickButton.button << std::endl;
            }
            if (event.type == sf::Event::JoystickMoved)
            {
                if (event.joystickMove.axis == sf::Joystick::X)
                {
                    std::cout << "X axis moved!" << std::endl;
                    std::cout << "joystick id: " << event.joystickMove.joystickId << std::endl;
                    std::cout << "new position: " << event.joystickMove.position << std::endl;
                }
                if (event.joystickMove.axis == sf::Joystick::Y)
                {
                    std::cout << "Y axis moved!" << std::endl;
                    std::cout << "joystick id: " << event.joystickMove.joystickId << std::endl;
                    std::cout << "new position: " << event.joystickMove.position << std::endl;
                }
                if (event.joystickMove.axis == sf::Joystick::Z)
                {
                    std::cout << "Z axis moved!" << std::endl;
                    std::cout << "joystick id: " << event.joystickMove.joystickId << std::endl;
                    std::cout << "new position: " << event.joystickMove.position << std::endl;
                }
                if (event.joystickMove.axis == sf::Joystick::R)
                {
                    std::cout << "R axis moved!" << std::endl;
                    std::cout << "joystick id: " << event.joystickMove.joystickId << std::endl;
                    std::cout << "new position: " << event.joystickMove.position << std::endl;
                }
                if (event.joystickMove.axis == sf::Joystick::U)
                {
                    std::cout << "U axis moved!" << std::endl;
                    std::cout << "joystick id: " << event.joystickMove.joystickId << std::endl;
                    std::cout << "new position: " << event.joystickMove.position << std::endl;
                }
                if (event.joystickMove.axis == sf::Joystick::V)
                {
                    std::cout << "V axis moved!" << std::endl;
                    std::cout << "joystick id: " << event.joystickMove.joystickId << std::endl;
                    std::cout << "new position: " << event.joystickMove.position << std::endl;
                }
            }
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                    std::cout << "wheel type: vertical" << std::endl;
                else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
                    std::cout << "wheel type: horizontal" << std::endl;
                else                if (event.joystickMove.axis == sf::Joystick::Y)
                {
                    std::cout << "Y axis moved!" << std::endl;
                    std::cout << "joystick id: " << event.joystickMove.joystickId << std::endl;
                    std::cout << "new position: " << event.joystickMove.position << std::endl;
                }
                    std::cout << "wheel type: unknown" << std::endl;
                std::cout << "wheel movement: " << event.mouseWheelScroll.delta << std::endl;
                std::cout << "mouse x: " << event.mouseWheelScroll.x << std::endl;
                std::cout << "mouse y: " << event.mouseWheelScroll.y << std::endl;
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    std::cout << "the right button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                }
            }
            if (event.type == sf::Event::MouseMoved)
            {
                std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
                std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}