#ifndef PERSO_H_INCLUDED
#define PERSO_H_INCLUDED

#include <SFML/Graphics.hpp>


class Perso
{
  public:
    Perso(int num, const  sf::Texture& texture);
    void setPos(sf::Vector2f);
    void move(float ElapsedTime);
    sf::Sprite getSprite(float ElapsedTime);
    int getRectW();
    int getRectH();
    sf::Vector2f getCenter();
    void reset();
    bool isAlive();
    void dead();
    void incScore(int points);
    int getScore();
    int getBestScore();

  private:
    int m_num;
    int m_frame;
    sf::Vector2f m_size;
    float m_duration;
    const sf::Texture* m_texture;

    std::vector<sf::IntRect> m_anim;
    sf::Sprite m_sprite;
    int m_activeFrame;
    float m_speed;
    float m_time;
    bool m_alive;
    int m_score;
    int m_bestScore;
};

#endif // PERSO_H_INCLUDED

