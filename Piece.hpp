#ifndef PIECE_H_INCLUDED
#define PIECE_H_INCLUDED

#include <SFML/Graphics.hpp>

class Piece
{
  public:
    Piece(const  sf::Texture& texture);
    void setPos(sf::Vector2f);
    sf::Sprite getSprite(float elapsedTime);
    int getRectW();
    int getRectH();
    sf::Vector2f getCenter();

  private:
    int m_frame;
    float m_duration;
    const sf::Texture* m_texture;
    sf::Vector2f m_size;

    std::vector<sf::IntRect> m_anim;
    sf::Sprite m_sprite;
    int m_activeFrame;

    sf::Clock m_clock;
    float m_time;
};

#endif // PIECE_H_INCLUDED

