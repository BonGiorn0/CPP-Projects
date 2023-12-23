#include <SFML/Graphics.hpp>
#include <vector>

enum class ShapeType{
    LShape = 0,
    MirroredLShape,
    Square,
    ZShape,
    MirroredZShape,
    TShape,
    Stick
};

class Shape : public sf::Drawable
{
private:
    std::vector<sf::Sprite> rectangles;
    float tileSize;
    float speed = 0; // px\sec
    
public:
    Shape() = default;
    Shape(const Shape &other) = default;
    Shape(float x, float y, float size, 
        ShapeType shapeType, sf::Texture &texture);
    void MoveDown(sf::Time elapsedTime);
    void MoveSideway(sf::Keyboard::Key key);
    void setSpeed(float newSpeed);
    float getSpeed() const;
    sf::Color getColor() const;
    void Rotate();
    bool intersects(sf::FloatRect otherRect) const;
    bool contains(sf::Vector2f &point) const;
    virtual void draw (sf::RenderTarget &target, sf::RenderStates states) const override;
    virtual ~Shape() = default;
};