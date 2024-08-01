#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <math.h>
#include <list>
#include <filesystem>
#include "Rock.h"
#include "Bullet.h"
#include "MySprite.h"


bool PtInWindow(float left,float top,float right,float bottom, float x, float y)
{
    return ((x>left)&&(x<right)&&(y>top)&&(y<bottom));

}

bool is_deleted(const Bullet *b) { return (b->m_f_deleted==true); }

int RandomInt(int a, int b) 
{
	int diff = b - a + 1;
	int r = rand() % diff;
	return a + r;
}

void bounceScreenLimits( int left, int top, int right, int bottom, Rock *pRock)
{
    //------------------------------------------
    if ((pRock->left()<=left)||(pRock->right()>=right)){
        pRock->m_v.x = -pRock->m_v.x;    
    }

    if ((pRock->top()<=top)||(pRock->bottom()>=bottom)){
        pRock->m_v.y = -pRock->m_v.y;    
    }


}

int main()
{

    bool        fTrigger = false;
    int         iTriggerDelay = 0;
    std::list<Bullet *> list_bullets;


    float       speedA = 0.0f;
    float       speed = 0.0f;
    Bullet      *pBullet = NULL;

    Rock        *pRock1 = NULL;
    Rock        *pRock2 = NULL;

    srand(time(NULL));

    auto window = sf::RenderWindow{ { 800u, 600u }, "CMake SFML Project!!" };
    window.setFramerateLimit(144);

    sf::SoundBuffer buffer;
    std::filesystem::path resPath{".."};
    buffer.loadFromFile(resPath/"344276__nsstudios__laser3.wav");
    sf::Sound soundLaser;
    soundLaser.setBuffer(buffer);
    soundLaser.setVolume(50.0);


    int screenWidth = window.getSize().x;
    int screenHeight = window.getSize().y;

    int shipPosX = (screenWidth - 32)/2;
    int shipPosY = screenHeight - 3*32;
    MySprite    ship(shipPosX, shipPosY, 0.0);

    sf::Clock clock;
    sf::Time elapsed = clock.restart();

    float a = (float) RandomInt(0, 359);
    float vx = 2.0*cos(a*M_PI/180.0);
    float vy = 2.0*sin(a*M_PI/180.0);
    pRock1 = new Rock( 256.0, 256.0, vx, vy, 10.0);

    a = (float) RandomInt(0, 359);
    vx = 2.4*cos(a*M_PI/180.0);
    vy = 2.4*sin(a*M_PI/180.0);
    pRock2 = new Rock( 256.0, 256.0, vx, vy, 15.0);


    while (window.isOpen())
    {
        elapsed = clock.getElapsedTime();
        if (elapsed.asMilliseconds()<10){
            continue;
        }else{
            sf::Time elapsed = clock.restart();
        }

        //-------------------------------------------
        if (fTrigger){
            iTriggerDelay++;
        }

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
                }else if (event.key.code == sf::Keyboard::V){
                    a = (float) RandomInt(0, 359);
                    vx = 2.4*cos(a*M_PI/180.0);
                    vy = 2.4*sin(a*M_PI/180.0);
                    pRock1->setVelocity( vx, vy);
                    a = (float) RandomInt(0, 359);
                    vx = 2.4*cos(a*M_PI/180.0);
                    vy = 2.4*sin(a*M_PI/180.0);
                    pRock2->setVelocity( vx, vy);
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

        ship.createMask();
        ship.createMaskRect();

        pRock1->updatePosition();
        bounceScreenLimits(1,1,screenWidth-1,screenHeight-1,pRock1);

        pRock2->updatePosition();
        bounceScreenLimits(1,1,screenWidth-1,screenHeight-1,pRock2);

        if (fTrigger){
            if ((iTriggerDelay%24)==0){
                float angle = ship.getAngle();
                sf::Vector2f n = ship.m_n;
                sf::Vector2f pos = ship.m_pos;
                if ((pBullet = new Bullet(pos.x, pos.y, n.x,n.y))!=NULL){
                    list_bullets.push_back(pBullet);
                    soundLaser.play();
                    //printf(">>>%d %d : %d\n",alienPosX,alienPosY,iTriggerDelay);
                }
            }

        }

        //-- Update bullets positions
        for (auto pBullet : list_bullets){
            if (PtInWindow(10,10,screenWidth-10,screenHeight, pBullet->m_pos.x, pBullet->m_pos.y)){
                //-- In Windows compute new position
                pBullet->updatePos();
            }else{
                //-- Out off window => Mark as depreciate
                pBullet->m_f_deleted = true;
            }
        }

        //-- Remove depreciate bullets
        list_bullets.remove_if (is_deleted);

        window.clear();

        ship.draw(window);
        ship.drawReducedMaskRect(window);
        //ship.drawMaskRect(window);

        for (auto pBullet : list_bullets){
            pBullet->draw(window);
        }


        pRock1->draw(window);
        pRock2->draw(window);


        window.display();
    }

    //-- Free remaining bullets
    for (auto pBullet : list_bullets){
        delete pBullet;
    }
    list_bullets.clear();

    if (pRock1){
        delete pRock1;
    }

    if (pRock2){
        delete pRock2;
    }

    return 0;

}
