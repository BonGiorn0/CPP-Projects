#include <SFML/Graphics.hpp>

class Ball : public sf::Drawable{
public:
    Ball(float x = 20, float y = 20, float radius = 10);
    virtual ~Ball(){};
    float getX();
    float getY();
    float getRadius();
    sf::Vector2f getSpeed() const;
    bool intersects(const sf::FloatRect &rectangle);
    void setSpeed(sf::Vector2f newSpeed);
    void move(float elapsedTime);

private:
    virtual void draw (sf::RenderTarget &target, sf::RenderStates states) const;
    sf::CircleShape circle;
    sf::Vector2f velocity = sf::Vector2f(-300, 300);//px/sec
};