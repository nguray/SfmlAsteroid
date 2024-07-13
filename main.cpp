#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <list>
#include "Bullet.h"
#include "MySprite.h"

int main()
{

    bool        fTrigger = false;
    int         iTriggerDelay = 0;
    std::list<Bullet *> list_bullets;


    float       speedA = 0.0f;
    float       speed = 0.0f;

    auto window = sf::RenderWindow{ { 800u, 600u }, "CMake SFML Project!!" };
    window.setFramerateLimit(144);

    int screenWidth = window.getSize().x;
    int screenHeight = window.getSize().y;

    int shipPosX = (screenWidth - 32)/2;
    int shipPosY = screenHeight - 3*32;
    MySprite    ship(shipPosX, shipPosY, 0.0);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            switch(event.type){
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code==sf::Keyboard::Escape){
                    window.close();
                }else if (event.key.code == sf::Keyboard::Left){
                    speedA = -1.0f;
                }else if (event.key.code == sf::Keyboard::Right){
                    speedA = 1.0f;
                }else if (event.key.code == sf::Keyboard::Up){
                    speed = 1.0f;
                }else if (event.key.code == sf::Keyboard::Down){
                    speed = -1.0f;
                }else if (event.key.code == sf::Keyboard::Space){
                    if (!fTrigger){
                        fTrigger = true;
                        iTriggerDelay = 0;
                    }

                }
                break;
            case sf::Event::KeyReleased:
                if ((event.key.code == sf::Keyboard::Left)||
                    (event.key.code == sf::Keyboard::Right)){
                    speedA = 0;
                }
                if ((event.key.code == sf::Keyboard::Up)||
                    (event.key.code == sf::Keyboard::Down)){
                    speed = 0.0f;
                }
                if (event.key.code == sf::Keyboard::Space){
                    fTrigger = false;
                }
                break;
            default:

                break;
            }
        }

        if (speedA!=0.0f){
            float a = ship.getAngle() + speedA;
            ship.setAngle(a);
        }

        if (speed==0.0f){
            ship.idle();
        }else{
            if (speed>0.0f){
                ship.accelerate();
            }else{
                ship.decelerate();
            }
        }

        ship.updatePos();

        sf::Vector2f p = ship.m_pos;
        if ((p.x<0)||(p.x>screenWidth)){
            p.x = screenWidth - p.x;
        }
        if ((p.y<0)||(p.y>screenHeight)){
            p.y = screenHeight - p.y;
        }
        ship.m_pos = p;


        window.clear();

        ship.draw(window);

        window.display();
    }
}
