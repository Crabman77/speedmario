#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Platform.hpp"
#include "Button.hpp"
#include "Perso.hpp"
#include "Cake.hpp"
#include "Piece.hpp"
#include "Hud.hpp"


class Engine
{
    public:
        bool init(const char* titre);
        int menu();
        bool running();
        void stop();
        void cleanup();
        void mouseIsClicked();
        void launch(int callBack);
        void game(int nbPlayers);
        void newGame(int nb);
        sf::Vector2f randomPos(int w, int h);
        bool isCollide(sf::Vector2f p1, sf::Vector2f p2, int dist);

    private:
        int m_screenW;
        int m_screenH;
        int m_fps;
        sf::RenderWindow* m_window;
        sf::RenderTexture m_render;
        sf::View m_view;
        bool m_running;
        bool m_escPressed;
        unsigned int m_menuButtonSelected1;
        unsigned int m_menuButtonSelected2;
        bool m_mouseClicked;
        bool m_keyUpPressed;
        bool m_keyDownPressed;
        bool m_keyReturnPressed;
        std::vector<Cake*> m_cakes;

        sf::Font m_font;
        //sound
        sf::SoundBuffer m_bufferLost;
        sf::Sound m_soundLost;
        sf::SoundBuffer m_bufferPiece;
        sf::Sound m_soundPiece;

        //texture
        sf::Texture m_titleTexture;
        sf::Texture m_platformTexture;
        sf::Texture m_player1Texture;
        sf::Texture m_player2Texture;
        sf::Texture m_cakeTexture;
        sf::Texture m_pieceTexture;
        sf::Texture m_buttonsTexture;
        sf::Sprite m_menuSelected;
        Hud* m_hud;
        Platform* m_platform;
        Perso* m_player1;
        Perso* m_player2;
        Piece* m_piece;
        int m_playersAlive;
        int nbPlayers;
        sf::Text m_copyright;
        sf::Text m_version;
};

#endif
