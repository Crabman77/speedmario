#include "Button.hpp"

Button::Button(sf::Texture texture,sf::Vector2f pixelPos, int callBack, sf::Vector2f pos)
{
    m_pixelPos = pixelPos;
    m_size = sf::Vector2f(150, 40);
    m_texture = texture;
    m_callBack = callBack;
    m_pos = pos;
    m_sprite.setTexture(m_texture);
    for( int i = 0; i < 2; i++ )
    {
        m_anim.push_back(sf::IntRect(pixelPos.x+(m_size.x*i), pixelPos.y, m_size.x, m_size.y));
    }
    m_sprite.setTextureRect(m_anim[0]);
    m_sprite.setPosition(m_pos);
    m_active = false;
}


bool Button::update(sf::RenderWindow* window, bool mouseClicked)
{
    sf::FloatRect box = m_sprite.getGlobalBounds();
    sf::Vector2i mPos = sf::Mouse::getPosition(*window);
    sf::Vector2f worldPos = window->mapPixelToCoords(mPos);
    if (box.contains(worldPos))
    {
        if (!m_active)
        {
            m_sprite.setTextureRect(m_anim[1]);
            m_active = true;
        }
        bool clicked = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        if (!m_pressed && clicked && !mouseClicked)
        {
            m_pressed = true;
            return true;
        }else if (!clicked)
        {
            m_pressed = false;
        }
    } else
    {
        if (m_active)
        {
            m_sprite.setTextureRect(m_anim[0]);
            m_active = false;
        }
        m_pressed = false;
    }
    return false;
}


int Button::getCallBack()
{
    return m_callBack;
}
sf::Vector2f Button::getPosition()
{
    return m_sprite.getPosition();
}

sf::Sprite Button::getSprite()
{
    return m_sprite;
}
