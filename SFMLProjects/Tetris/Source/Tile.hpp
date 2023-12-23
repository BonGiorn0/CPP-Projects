#include <SFML/Graphics.hpp>
#include <stddef.h>

class Tile : public sf::Drawable
{
private:
    sf::Sprite sprite;
    float tileSize = 13;
    bool obstackleState = false;
public:
    Tile() = delete;
    Tile(float x, float y, float size);
    Tile(const Tile& other);
    //Tile(Tile &&other);
    Tile &operator=(const Tile& other);
    //Tile &operator=(Tile&& other);
    void setTexture(sf::Texture &texture);
    void setIsObstackle(bool state);
    void setColor(sf::Color color);
    sf::Vector2f getPosition() const;
    sf::FloatRect getGloabalBounds() const;
    bool isObstackle();
    virtual void draw (sf::RenderTarget &target, sf::RenderStates states) const override;
    virtual ~Tile() = default;
};
