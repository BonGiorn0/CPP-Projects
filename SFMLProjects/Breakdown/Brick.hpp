#include <SFML/Graphics.hpp>

class Brick : public sf::Drawable{
public:
    Brick(float x, float y, float width, float height);
    Brick(const Brick& other);
    virtual ~Brick();
    float getX();
    float getY();
    float getWidth();
    float getHeight();
    sf::FloatRect getGlobalBounds();
    static size_t objCount;
private:
    virtual void draw (sf::RenderTarget &target, sf::RenderStates states) const;
    sf::RectangleShape rectangle;
};