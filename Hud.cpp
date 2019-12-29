#include <iostream>
#include "Hud.hpp"


Hud::Hud(sf::Font& font)
{
    //player 1
    // score 1
    m_scoreText1.setFont(font);
    m_scoreText1.setCharacterSize(24);
    m_scoreText1.setFillColor(sf::Color::White);
    m_scoreText1.setPosition( sf::Vector2f(40,320) );
    m_scoreText1.setString("Score");

    m_score1.setFont(font);
    m_score1.setCharacterSize(24);
    m_score1.setFillColor(sf::Color::White);
    m_score1.setPosition( sf::Vector2f(60,350) );
    m_score1.setString("0");

    //best 1
    m_bestScoreText1.setFont(font);
    m_bestScoreText1.setCharacterSize(24);
    m_bestScoreText1.setFillColor(sf::Color::White);
    m_bestScoreText1.setPosition( sf::Vector2f(40,380) );
    m_bestScoreText1.setString("Best");

    m_bestScore1.setFont(font);
    m_bestScore1.setCharacterSize(24);
    m_bestScore1.setFillColor(sf::Color::White);
    m_bestScore1.setPosition( sf::Vector2f(60,410) );
    m_bestScore1.setString("0");

    //player 2
    // score 2
    m_scoreText2.setFont(font);
    m_scoreText2.setCharacterSize(24);
    m_scoreText2.setFillColor(sf::Color::White);
    m_scoreText2.setPosition( sf::Vector2f(790,320) );
    m_scoreText2.setString("Score");

    m_score2.setFont(font);
    m_score2.setCharacterSize(24);
    m_score2.setFillColor(sf::Color::White);
    m_score2.setPosition( sf::Vector2f(810,350) );
    m_score2.setString("0");

    //best 2
    m_bestScoreText2.setFont(font);
    m_bestScoreText2.setCharacterSize(24);
    m_bestScoreText2.setFillColor(sf::Color::White);
    m_bestScoreText2.setPosition( sf::Vector2f(790,380) );
    m_bestScoreText2.setString("Best");

    m_bestScore2.setFont(font);
    m_bestScore2.setCharacterSize(24);
    m_bestScore2.setFillColor(sf::Color::White);
    m_bestScore2.setPosition( sf::Vector2f(810,410) );
    m_bestScore2.setString("0");
}

void Hud::updatePlayer1(const int score, const int bestScore)
{
    std::string scoreText = std::to_string(score);
    m_score1.setString(scoreText);

    std::string bestScoreText = std::to_string(bestScore);
    m_bestScore1.setString(bestScoreText);
}

void Hud::updatePlayer2(const int score, const int bestScore)
{
    std::string scoreText = std::to_string(score);
    m_score2.setString(scoreText);

    std::string bestScoreText = std::to_string(bestScore);
    m_bestScore2.setString(bestScoreText);
}


void Hud::reset()
{
    m_score1.setString("0");
    m_score2.setString("0");
}


void Hud::draw(sf::RenderTexture* render)
{
    // player 1
    render->draw(m_scoreText1);
    render->draw(m_score1);
    render->draw(m_bestScoreText1);
    render->draw(m_bestScore1);

   // player 2
   render->draw(m_scoreText2);
   render->draw(m_score2);
   render->draw(m_bestScoreText2);
   render->draw(m_bestScore2);
}

