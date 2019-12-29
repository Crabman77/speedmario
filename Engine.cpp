#include "Engine.hpp"


bool Engine::init(const char* titre)
{
    m_screenW = 900;
    m_screenH = 650;
    m_running = true;
    m_fps = 30;
    m_window = new sf::RenderWindow(sf::VideoMode(m_screenW, m_screenH), titre);
    //m_window->setFramerateLimit(m_fps);
    m_window->setVerticalSyncEnabled(true);

    srand(time(NULL));

    // sound lost
    if (!m_bufferLost.loadFromFile("sounds/lost.ogg"))
    {
        std::cerr << "Error during import sounds/lost.ogg" << std::endl;
        return false;
    }
    m_soundLost.setBuffer(m_bufferLost);

    // sound piece
    if (!m_bufferPiece.loadFromFile("sounds/piece.ogg"))
    {
        std::cerr << "Error during import sounds/piece.ogg" << std::endl;
        return false;
    }
    m_soundPiece.setBuffer(m_bufferPiece);

    // font
    if (!m_font.loadFromFile("font/default.ttf"))
    {
        std::cerr << "Error during import font/default.ttf" << std::endl;
        return false;
    }

    // tile
    if(!m_titleTexture.loadFromFile("textures/title.png"))
    {
        std::cerr << "Error during import textures/title.png" << std::endl;
        return false;
    }

    // platform
    if(!m_platformTexture.loadFromFile("textures/platform.png"))
    {
        std::cerr << "Error during import textures/platform.png" << std::endl;
        return false;
    }

     // player1
    if(!m_player1Texture.loadFromFile("textures/player1.png"))
    {
        std::cerr << "Error during import textures/player1.png" << std::endl;
        return false;
    }

     // player2
    if(!m_player2Texture.loadFromFile("textures/player2.png"))
    {
        std::cerr << "Error during import textures/player2.png" << std::endl;
        return false;
    }

     // cakes
    if(!m_cakeTexture.loadFromFile("textures/cake.png"))
    {
        std::cerr << "Error during import textures/cake.png" << std::endl;
        return false;
    }
     // piece
    if(!m_pieceTexture.loadFromFile("textures/piece.png"))
    {
        std::cerr << "Error during import textures/piece.png" << std::endl;
        return false;
    }

    // buttons
    if(!m_buttonsTexture.loadFromFile("textures/buttons.png"))
    {
        std::cerr << "Error during import textures/speedtiles.png" << std::endl;
        return false;
    }

    //create platform
    m_hud =  new Hud(m_font);
    m_platform = new Platform(m_platformTexture);

    //create players
    m_player1 = new Perso(1, m_player1Texture);
    m_player2 = new Perso(2, m_player2Texture);

    //create piece
    m_piece = new Piece(m_pieceTexture);

    // menu selected
    m_menuSelected.setTexture(m_buttonsTexture);
    m_menuSelected.setTextureRect(sf::IntRect(0, 0, 190, 40));

    m_copyright.setFont(m_font);
    m_copyright.setCharacterSize(18);
    m_copyright.setFillColor(sf::Color::White);
    m_copyright.setString("By Cr@bman");
    m_copyright.setPosition( sf::Vector2f((m_screenW/2)-50, m_screenH-25) );

    m_version.setFont(m_font);
    m_version.setCharacterSize(18);
    m_version.setFillColor(sf::Color::White);
    m_version.setString("V 0.1 2016");
    m_version.setPosition( sf::Vector2f(m_screenW-260, m_screenH-25) );

    m_render.create(m_screenW, m_screenH);
    m_view.setCenter(sf::Vector2f(m_screenW/2, m_screenH/2));
    m_view.setSize(sf::Vector2f(900, 650));
    m_window->setView(m_view);
    return true;
}


bool Engine::running()
{
    return m_running;
}


void Engine::stop()
{
    m_window->close();
    m_running = false;
}


void Engine::cleanup()
{
    delete m_platform;
    delete m_player1;
    delete m_player2;
    delete m_piece;
    delete m_window;
}


void Engine::mouseIsClicked()
{
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        m_mouseClicked = false;
    }
}


int Engine::menu()
{
    m_menuButtonSelected1 = 0;
    sf::Sprite titleSprite(m_titleTexture);
    titleSprite.setPosition(sf::Vector2f(222.5, 30));

    // menu
    std::vector<Button*> buttons;
    buttons.push_back(new Button(m_buttonsTexture, sf::Vector2f(0, 40), 0, sf::Vector2f(375, 300)));
    buttons.push_back(new Button(m_buttonsTexture, sf::Vector2f(0, 80), 1, sf::Vector2f(375, 370)));
    buttons.push_back(new Button(m_buttonsTexture, sf::Vector2f(0, 120), 2, sf::Vector2f(375, 440)));

    while (running())
    {
        mouseIsClicked();
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                if (!m_escPressed)
                {
                    m_escPressed = true;
                    stop();
                    break;
                }
            }else{
                m_escPressed = false;
            }

            if (event.type == sf::Event::Resized)
            {
                float nW = (float)(event.size.width) / (float)(m_screenW);
                float nH = (float)(event.size.height) / (float)(m_screenH);
                float scale = nH;
                if (nW < nH)
                    scale = nW;
                m_view.setSize(sf::Vector2f(event.size.width, event.size.height));
                m_view.zoom(1/scale);
                m_window->setView(m_view);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (m_menuButtonSelected1 > 0 && !m_keyUpPressed)
            {
                m_menuButtonSelected1--;
                m_keyUpPressed = true;
            }
        }else
        {
            m_keyUpPressed = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if (m_menuButtonSelected1 < buttons.size()-1 && !m_keyDownPressed)
            {
                m_menuButtonSelected1++;
                m_keyDownPressed = true;
            }
        }else
        {
            m_keyDownPressed = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            if (!m_keyReturnPressed)
            {
                launch(m_menuButtonSelected1);
            }
        }else
        {
            m_keyReturnPressed = false;
        }

        m_window->clear(sf::Color::Blue);
        m_render.clear(sf::Color::Blue);
        m_render.draw(titleSprite);

        for (unsigned int i=0;i<buttons.size();i++)
        {
            if (buttons[i]->update(m_window, m_mouseClicked))
            {
                m_mouseClicked = true;
                launch(buttons[i]->getCallBack());
            }
            m_render.draw(buttons[i]->getSprite());
        }
        sf::Vector2f pos = buttons[m_menuButtonSelected1]->getPosition();
        m_menuSelected.setPosition(pos.x-20, pos.y);
        m_render.draw(m_menuSelected);
        m_render.draw(m_copyright);
        m_render.draw(m_version);
        m_render.display();
        const sf::Texture& texture = m_render.getTexture();
        sf::Sprite sprite(texture);
        m_window->draw(sprite);
        m_window->display();
    }

    for(size_t i = 0; i < buttons.size(); i++)
        delete(buttons[i]);

    return EXIT_SUCCESS;
}


void Engine::launch(int callBack)
{
    switch (callBack)
    {
        case 0:
        {
            game(1);
            break;
        }
        case 1:
        {
            game(2);
            break;
        }
        case 2:
        {
            stop();
        }
    }
}


void Engine::game(int nb)
{
    nbPlayers = nb;
    bool ingame = true;
    // menu
    std::vector<Button*> buttons;
    buttons.push_back(new Button(m_buttonsTexture, sf::Vector2f(0, 160), 0, sf::Vector2f(375, 300)));
    buttons.push_back(new Button(m_buttonsTexture, sf::Vector2f(0, 200), 1, sf::Vector2f(375, 370)));
    m_menuButtonSelected2 = 0;

    newGame(nbPlayers);
    sf::Clock time;
    while (running() && ingame)
    {
        float elapsedTime = time.restart().asSeconds();
        mouseIsClicked();
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                if (!m_escPressed)
                {
                    m_escPressed = true;
                    ingame = false;
                    break;
                }
            }else{
                m_escPressed = false;
            }

            if (event.type == sf::Event::Resized)
            {
                float nW = (float)(event.size.width) / (float)(m_screenW);
                float nH = (float)(event.size.height) / (float)(m_screenH);
                float scale = nH;
                if (nW < nH)
                    scale = nW;
                m_view.setSize(sf::Vector2f(event.size.width, event.size.height));
                m_view.zoom(1/scale);
                m_window->setView(m_view);
            }
        }

        m_window->clear(sf::Color::Blue);
        m_render.clear(sf::Color::Blue);

        if (m_playersAlive > 0)
        {
            m_platform->clear();
            m_platform->drawSprite(m_piece->getSprite(elapsedTime));

            for(unsigned int i=0;i<m_cakes.size();i++){
                m_cakes[i]->move(elapsedTime);
                m_platform->drawSprite(m_cakes[i]->getSprite(elapsedTime));
                if(!m_cakes[i]->isDangerous())
                    continue;
                if (m_player1->isAlive() && isCollide(m_player1->getCenter(), m_cakes[i]->getCenter(), 20) )
                {
                    m_soundLost.play();
                    m_player1->dead();
                    m_playersAlive--;
                }
                if (nbPlayers == 2 && m_player2->isAlive() && isCollide(m_player2->getCenter(), m_cakes[i]->getCenter(), 20) )
                {
                    m_soundLost.play();
                    m_player2->dead();
                    m_playersAlive--;
                }
            }

            if (m_player1->isAlive())
            {
                m_player1->move(elapsedTime);
                //if touch piece
                if ( isCollide(m_player1->getCenter(), m_piece->getCenter(), 16) )
                {
                    m_piece->setPos(randomPos(14, 16));
                    m_player1->incScore(5);
                    m_hud->updatePlayer1(m_player1->getScore(), m_player1->getBestScore());

                    //add cake
                    if (m_cakes.size() < 30)
                        m_cakes.push_back(new Cake(m_cakeTexture, randomPos(20, 20)));
                    m_soundPiece.play();
                }
                m_platform->drawSprite(m_player1->getSprite(elapsedTime));
            }

            if (nbPlayers == 2 && m_player2->isAlive())
            {
                m_player2->move(elapsedTime);
                //if touch piece
                if ( isCollide(m_player2->getCenter(), m_piece->getCenter(), 16) )
                {
                    m_piece->setPos(randomPos(14, 16));
                    m_player2->incScore(5);
                    m_hud->updatePlayer2(m_player2->getScore(), m_player2->getBestScore());
                    //add cake
                    if (m_cakes.size() < 30)
                        m_cakes.push_back(new Cake(m_cakeTexture, randomPos(20, 20)));
                    m_soundPiece.play();
                }
                m_platform->drawSprite(m_player2->getSprite(elapsedTime));
            }
            m_platform->update();
        }

        m_render.draw(m_platform->getSprite());
        m_hud->draw(&m_render);

        if (m_playersAlive == 0)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                if (m_menuButtonSelected2 > 0 && !m_keyUpPressed)
                {
                    m_menuButtonSelected2--;
                    m_keyUpPressed = true;
                }
            }else
            {
                m_keyUpPressed = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                if (m_menuButtonSelected2 < buttons.size()-1 && !m_keyDownPressed)
                {
                    m_menuButtonSelected2++;
                    m_keyDownPressed = true;
                }
            }else
            {
                m_keyDownPressed = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                if (!m_keyReturnPressed)
                {
                    m_keyReturnPressed = true;
                    switch (m_menuButtonSelected2)
                    {
                        case 0:
                        {
                            newGame(nbPlayers);
                            break;
                        }
                        case 1:
                        {
                            ingame = false;
                            break;
                        }
                    }
                }
            }else
            {
                m_keyReturnPressed = false;
            }

            //buttons
            for (unsigned int i=0;i<buttons.size();i++)
            {
                if (buttons[i]->update(m_window, m_mouseClicked))
                {
                    m_mouseClicked = true;
                    switch (buttons[i]->getCallBack())
                    {
                        case 0:
                        {
                            newGame(nbPlayers);
                            break;
                        }
                         case 1:
                        {
                            ingame = false;
                            break;
                        }
                    }
                }
                m_render.draw(buttons[i]->getSprite());
            }
            sf::Vector2f pos = buttons[m_menuButtonSelected2]->getPosition();
            m_menuSelected.setPosition(pos.x-20, pos.y);
            m_render.draw(m_menuSelected);

        }
        m_render.draw(m_copyright);
        m_render.draw(m_version);
        m_render.display();
        const sf::Texture& texture = m_render.getTexture();
        sf::Sprite sprite(texture);
        m_window->draw(sprite);
        m_window->display();
    }

    for(size_t i = 0; i < m_cakes.size(); i++)
        delete(m_cakes[i]);
    m_cakes.clear();

    for(size_t i = 0; i < buttons.size(); i++)
        delete(buttons[i]);
}

void Engine::newGame(int nb)
{
	if (m_cakes.size() > 0)
	{
        for(size_t i = 0; i < m_cakes.size(); i++)
            delete(m_cakes[i]);
        m_cakes.clear();
    }
    m_player1->reset();
    m_player1->setPos(randomPos(20, 26));
    m_player2->reset();
    m_player2->setPos(randomPos(20, 26));
    m_piece->setPos(randomPos(14, 16));
    m_hud->reset();
    m_playersAlive = nb;
}


sf::Vector2f Engine::randomPos(int w, int h)
{
    int x = rand()%(600-w);
    int y = rand()%(600-h);
    return sf::Vector2f(x, y);
}


bool Engine::isCollide(sf::Vector2f p1, sf::Vector2f p2, int dist)
{
    int distpb = sqrt(pow(p2.x-p1.x,2)+ pow(p2.y-p1.y,2));
    if (distpb < dist)
        return true;
    return false;
}

