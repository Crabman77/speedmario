#include "Cake.hpp"

enum { LEFT, RIGHT, UP, DOWN };


Cake::Cake(const sf::Texture& texture, sf::Vector2f newPos)
{
    m_frame = 2;
    m_size = sf::Vector2f(20, 20);
    m_duration = 0.6;
    m_texture = &texture;
    m_sprite.setTexture(*m_texture);
    for( int i = 0; i < m_frame; i++ )
    {
        m_anim.push_back(sf::IntRect(i*m_size.x, 0, m_size.x, m_size.y));
    }

    m_activeFrame = 0;
    m_sprite.setTextureRect(m_anim[m_activeFrame]);
    m_sprite.setPosition(newPos);
    m_direction = rand() % 4;
    m_speed = 120;
    m_time = 0;
    m_dangerous = false;
    m_time_dangerous = 0;
}


void Cake::move(float elapsedTime)
{
    if(!m_dangerous)
    {
        m_time_dangerous += elapsedTime;
        if (m_time_dangerous > 2)
            m_dangerous = true;
        return;
    }

    sf::Vector2f pos = m_sprite.getPosition();
    sf::IntRect rect = m_sprite.getTextureRect();
    float speed = m_speed * elapsedTime;
    float movement;
    switch(m_direction)
    {
        case LEFT:
            if(pos.x > 0)
            {
                movement = pos.x - speed;
                if(movement < 0)
                    speed += movement;
                m_sprite.move(-speed, 0.0);
            }else
            {
                m_direction = RIGHT;
            }
            break;
        case RIGHT:
            if(pos.x+rect.width < 600)
            {
                movement = pos.x + rect.width + speed - 600;
                if (movement >= 0)
                    speed -= movement;
                m_sprite.move(speed, 0.0);
            }else
            {
               m_direction = LEFT;
            }
            break;
        case UP:
            if(pos.y > 0)
            {
                movement = pos.y - speed;
                if(movement < 0)
                    speed += movement;
                m_sprite.move(0.0, -speed);
            }else
            {
                m_direction = DOWN;
            }
            break;
        default:
            if(pos.y+rect.height < 600)
            {
                movement = pos.y + rect.height + speed - 600;
                if (movement >= 0)
                    speed -= movement;
                m_sprite.move(0.0, speed);
            }else
            {
                m_direction = UP;
            }
            break;
    }
}


sf::Sprite Cake::getSprite(float elapsedTime)
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


bool Cake::isDangerous()
{
    return m_dangerous;
}


sf::Vector2f Cake::getCenter()
{
    sf::Vector2f pos = m_sprite.getPosition();
    sf::IntRect rect = m_sprite.getTextureRect();
    return sf::Vector2f(pos.x+(rect.width/2), pos.y+(rect.height/2));
}

int Cake::getRectW()
{
    sf::IntRect tRect = m_sprite.getTextureRect();
    return tRect.width;
}


int Cake::getRectH()
{
    sf::IntRect tRect = m_sprite.getTextureRect();
    return tRect.height;
}

