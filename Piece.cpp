#include "Piece.hpp"

Piece::Piece(const  sf::Texture& texture)
{
    m_frame = 6;
    m_size = sf::Vector2f(14, 16);
    m_duration = 1.4;
    m_texture = &texture;
    m_sprite.setTexture(*m_texture);
    for( int i = 0; i < m_frame; i++ )
    {
        m_anim.push_back(sf::IntRect(m_size.x*i, 0, m_size.x, m_size.y));
    }
    m_activeFrame = 0;
    m_sprite.setTextureRect(m_anim[m_activeFrame]);
    m_time = 0;
}

void Piece::setPos(sf::Vector2f pos)
{
    m_sprite.setPosition(pos);
}


int Piece::getRectW()
{
    sf::IntRect tRect = m_sprite.getTextureRect();
    return tRect.width;
}


int Piece::getRectH()
{
    sf::IntRect tRect = m_sprite.getTextureRect();
    return tRect.height;
}



sf::Sprite Piece::getSprite(float elapsedTime)
{
    m_time += elapsedTime;
    if (m_time > m_duration)
    {
        m_time = 0;
        m_activeFrame = 0;
        m_sprite.setTextureRect(m_anim[m_activeFrame]);
    }else
    {
        for (int i = 1; i <= m_frame; i++)
        {
            if (m_time < (m_duration/m_frame)*i)
            {
                int f = i-1;
                if (m_activeFrame != f)
                {
                     m_activeFrame = f;
                     m_sprite.setTextureRect(m_anim[m_activeFrame]);
                }
                break;
            }
        }
    }
    return m_sprite;
}


sf::Vector2f Piece::getCenter()
{
    sf::Vector2f pos = m_sprite.getPosition();
    sf::IntRect rect = m_sprite.getTextureRect();
    return sf::Vector2f(pos.x+(rect.width/2), pos.y+(rect.height/2));
}

