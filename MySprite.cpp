#include <math.h>
#include "MySprite.h"
#include <filesystem>
#include <iostream>
#include <string>

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
    std::filesystem::path resPath{".."};
    //std::cout << resPath/(std::string("Plan00") + ".png") << std::endl;
    m_Tex0.loadFromFile(resPath/"Plane00.png");
    m_Tex1.loadFromFile(resPath/"Plane01.png");
    m_Tex2.loadFromFile(resPath/"Plane02.png");
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

void MySprite::accelerate()
{
    m_v += 0.005f * m_n;
    setTexture(m_Tex1);

}

void MySprite::idle()
{
    setTexture(m_Tex0);
    
}

void MySprite::decelerate()
{
    m_v -= 0.001f * m_n;
    setTexture(m_Tex2);    
}

void MySprite::updatePos()
{
    m_pos += m_v;
}
