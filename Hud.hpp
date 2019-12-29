#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED

#include <SFML/Graphics.hpp>

class Hud
{
    public:
        Hud(sf::Font& font);
        void update();
        void reset();
        void updatePlayer1(const int score,const int bestScore);
        void updatePlayer2(const int score,const int bestScore);
        void draw(sf::RenderTexture* render);

    private:
        //score
        sf::Text m_scoreText1;
        sf::Text m_score1;
        sf::Text m_bestScoreText1;
        sf::Text m_bestScore1;

        sf::Text m_scoreText2;
        sf::Text m_score2;
        sf::Text m_bestScoreText2;
        sf::Text m_bestScore2;
};

#endif // HUD_H_INCLUDED

