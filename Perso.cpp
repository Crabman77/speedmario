#include "Perso.hpp"

Perso::Perso(int num, const sf::Texture& texture)
{
    m_num = num;
    m_frame = 2;
    m_texture = &texture;
    m_size = sf::Vector2f(20, 26);
    m_duration = 1.2;
    m_activeFrame = 0;
    m_speed = 240;
    m_sprite.setTexture(*m_texture);
    for( int i = 0; i < m_frame; i++ )
    {
        m_anim.push_back(sf::IntRect(m_size.x*i, 0, m_size.x, m_size.y));
    }
    m_sprite.setTextureRect(m_anim[m_activeFrame]);
    m_time = 0;
    m_score = 0;
    m_bestScore = 0;
}


void Perso::setPos(sf::Vector2f pos)
{
    m_sprite.setPosition(pos);
}


int Perso::getRectW()
{
    sf::IntRect tRect = m_sprite.getTextureRect();
    return tRect.width;
}


int Perso::getRectH()
{
    sf::IntRect tRect = m_sprite.getTextureRect();
    return tRect.height;
}


void Perso::move(float ElapsedTime)
{
    sf::Vector2f pos = m_sprite.getPosition();
    sf::IntRect rect = m_sprite.getTextureRect();
    float speed = m_speed * ElapsedTime;
    float movement;
    if (m_num == 1)
    {
        // LEFT
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if(pos.x  > 0)
            {
                movement = pos.x - speed;
                if(movement < 0)
                    speed += movement;
                m_sprite.move(-speed, 0.0);
            }
         // RIGHT
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if(pos.x+rect.width < 600)
            {
                movement = pos.x + rect.width + speed - 600;
                if (movement >= 0)
                    speed -= movement;
                m_sprite.move(speed, 0.0);
            }
        }

        // UP
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if(pos.y > 0)
            {
                movement = pos.y - speed;
                if(movement < 0)
                    speed += movement;
                m_sprite.move(0.0, -speed);
            }
        }
        // DOWN
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if(pos.y+rect.height < 600)
            {
                movement = pos.y + rect.height + speed - 600;
                if (movement >= 0)
                    speed -= movement;
                m_sprite.move(0.0, speed);
            }
        }
    }else
    {
        // LEFT
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            if(pos.x  > 0)
            {
                movement = pos.x - speed;
                if(movement < 0)
                    speed += movement;
                m_sprite.move(-speed, 0.0);
            }
         // RIGHT
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            if(pos.x+rect.width < 600)
            {
                movement = pos.x + rect.width + speed - 600;
                if (movement >= 0)
                    speed -= movement;
                m_sprite.move(speed, 0.0);
            }
        }

        // UP
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            if(pos.y > 0)
            {
                movement = pos.y - speed;
                if(movement < 0)
                    speed += movement;
                m_sprite.move(0.0, -speed);
            }
        }
        // DOWN
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            if(pos.y+rect.height < 600)
            {
                movement = pos.y + rect.height + speed - 600;
                if (movement >= 0)
                    speed -= movement;
                m_sprite.move(0.0, speed);
            }
        }
    }
}


sf::Sprite Perso::getSprite(float elapsedTime)
{
    m_time += elapsedTime;
    if (m_time > m_duration)
    {
        m_time = 0;
        m_activeFrame = 0;
        m_sprite.setTextureRect(m_anim[m_activeFrame]);
    }else
    {
        float tt = m_duration/m_frame;
        for (int i = 1; i <= m_frame; i++)
        {
            if (m_time < tt*i)
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


sf::Vector2f Perso::getCenter()
{
    sf::Vector2f pos = m_sprite.getPosition();
    sf::IntRect rect = m_sprite.getTextureRect();
    return sf::Vector2f(pos.x+(rect.width/2), pos.y+(rect.height/2));
}



void Perso::reset()
{
    m_alive = true;
    m_score = 0;
}



bool Perso::isAlive()
{
    return m_alive;
}


void Perso::dead()
{
    m_alive = false;
}


void Perso::incScore(int points)
{
    m_score += points;
    if (m_score > m_bestScore)
        m_bestScore = m_score;
}


int Perso::getScore()
{
    return m_score;
}


int Perso::getBestScore()
{
    return m_bestScore;
}

