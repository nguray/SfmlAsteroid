#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class MySprite : public sf::Sprite
{
public:
    MySprite();
    MySprite(float x, float y, float a);
    ~MySprite();

    float           m_Rad_Deg;
    float           m_angle;
    sf::Vector2f    m_v;
    sf::Vector2f    m_pos;
    sf::Vector2f    m_n;

    sf::Texture     m_Tex0;
    sf::Texture     m_Tex1;
    sf::Texture     m_Tex2;

    void setAngle(float a);
    float getAngle();
    void draw(sf::RenderWindow &window);
    void accelerate();
    void idle();
    void decelerate();
    void updatePos();


};