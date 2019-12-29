#include "Platform.hpp"


Platform::Platform(const sf::Texture& texture)
{
    m_texture = &texture;
    m_sprite.setTexture(*m_texture);
    m_render.create(600, 600);
    m_platform.setPosition(150, 25);
}


void Platform::drawSprite(sf::Sprite sprite)
{
     m_render.draw(sprite);
}


sf::Sprite Platform::getSprite()
{
    return m_platform;
}


void Platform::clear()
{
    m_render.clear(sf::Color::Blue);
    m_render.draw(m_sprite);
}


void Platform::update()
{
    m_render.display();
    m_platform.setTexture(m_render.getTexture());
}

