#include <SFML/Graphics.hpp>

class Paddle : public sf::Drawable{
public:
    Paddle(float x = 0, float y = 0, float width = 100, float height = 30);
    virtual ~Paddle() = default;
    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;
    float getSpeed();
    sf::FloatRect getGlobalBounds();
    void setX(float x);
    void updatePrevPosition();
private:
    virtual void draw (sf::RenderTarget &target, sf::RenderStates states) const;
    sf::RectangleShape rectangle;
    sf::Clock clock;
    float prevPosition;
    float currPosition;
    
};