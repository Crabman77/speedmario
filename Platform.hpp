#ifndef PLATFORM_H_INCLUDED
#define PLATFORM_H_INCLUDED

#include <SFML/Graphics.hpp>


class Platform
{
    public:
        Platform(const sf::Texture& texture);
        void drawSprite(sf::Sprite);
        sf::Sprite getSprite();
        void clear();
        void update();

    private:
        const sf::Texture* m_texture;
        sf::Sprite m_sprite;
        sf::RenderTexture m_render;
        sf::Sprite m_platform;
};

#endif // PLATFORM_H_INCLUDED

