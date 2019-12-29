#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Button
{
    public:
        Button(sf::Texture texture,sf::Vector2f pixelPos, int callBack, sf::Vector2f pos);
        bool update(sf::RenderWindow* window, bool mouseClicked);
        sf::Sprite getSprite();
        sf::Vector2f getPosition();
        int getCallBack();

    private:
        sf::Vector2f m_pixelPos;
        sf::Vector2f m_size;
        sf::Texture m_texture;
        int m_callBack;
        sf::Vector2f m_pos;
        sf::Sprite m_sprite;
        std::vector<sf::IntRect> m_anim;
        bool m_active;
        bool m_pressed;
};

#endif

