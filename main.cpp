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

    MySprite    ship(400.0,300.0,0.0);

    auto window = sf::RenderWindow{ { 800u, 600u }, "CMake SFML Project!!" };
    window.setFramerateLimit(144);

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

                }else if (event.key.code == sf::Keyboard::Right){

                }else if (event.key.code == sf::Keyboard::Up){

                }else if (event.key.code == sf::Keyboard::Down){

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
                    //speedA = 0;
                }
                if ((event.key.code == sf::Keyboard::Up)||
                    (event.key.code == sf::Keyboard::Down)){
                    //speed = 0.0f;
                }
                if (event.key.code == sf::Keyboard::Space){
                    fTrigger = false;
                }
                break;
            default:

                break;
            }
        }

        window.clear();

        ship.draw(window);

        window.display();
    }
}
