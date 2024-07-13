#include <math.h>
#include "MySprite.h"

MySprite::MySprite()
    :sf::Sprite(),m_pos(0.0,0.0),m_angle(0.0)
{
    setAngle(0.0);
}


MySprite::MySprite(float x, float y, float a)
    :sf::Sprite(),m_pos(x,y),
    m_n(0.0f,1.0f), m_Rad_Deg(M_PI/180.0f), 
    m_v(0.0f,0.0f)
{
    setAngle(a);
    m_Tex0.loadFromFile("../Plane00.png");
    m_Tex1.loadFromFile("../Plane01.png");
    m_Tex2.loadFromFile("../Plane02.png");
    setTexture(m_Tex0);
    setOrigin( 15.0f, 16.0f);

}

MySprite::~MySprite()
{

}

void MySprite::setAngle(float a)
{
    m_angle = a;
    m_n.x = cos( (a-90.0f) * m_Rad_Deg);
    m_n.y = sin( (a-90.0f) * m_Rad_Deg);
 
}

float MySprite::getAngle()
{
    return m_angle;
}

void MySprite::draw(sf::RenderWindow &window)
{
    setRotation(m_angle);
    setPosition(m_pos.x,m_pos.y);
    window.draw(*this);
}