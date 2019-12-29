#ifndef CAKE_H_INCLUDED
#define CAKE_H_INCLUDED

#include <SFML/Graphics.hpp>


class Cake
{
  public:
    Cake(const sf::Texture& texture, sf::Vector2f newPos);
    void move(float elapsedTime);
    sf::Sprite getSprite(float elapsedTime);
    bool isDangerous();
    sf::Vector2f getCenter();
    int getRectW();
    int getRectH();

  private:
    int m_frame;
    sf::Vector2f m_size;
    float m_duration;
    const sf::Texture* m_texture;
    bool m_dangerous;
    float m_time_dangerous;
    std::vector<sf::IntRect> m_anim;
    sf::Sprite m_sprite;
    int m_activeFrame;
    int m_direction;
    float m_speed;
    float m_time;
};

#endif // CAKE_H_INCLUDED
