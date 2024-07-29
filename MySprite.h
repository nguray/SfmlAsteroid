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

    sf::Image      m_mask;
    int            m_mask_dx;
    int            m_mask_dy;

    sf::IntRect    m_mask_rect;
    sf::IntRect    m_sub_mask_rect;
    sf::IntRect    m_intersect_rect;
    sf::IntRect    m_reduced_mask_rect;

    sf::Texture     m_Tex0;
    sf::Texture     m_Tex1;
    sf::Texture     m_Tex2;

    void translate(float dx,float dy,float srcX,float srcY,float &desX,float &desY);
    void rotate(float degA, float srcX,float srcY,float &desX,float &desY);
    void createMask();
    sf::IntRect createMaskRect();
    bool collide(MySprite &sprite);

    void setAngle(float a);
    float getAngle();
    void draw(sf::RenderWindow &window);
    void accelerate();
    void idle();
    void decelerate();
    void updatePos();

    void drawReducedMaskRect(sf::RenderWindow &window);
    void drawMaskRect(sf::RenderWindow &window);

};