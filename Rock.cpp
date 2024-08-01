#include "Rock.h"
#include <SFML/System/Vector2.hpp>

Rock::Rock(float x,float y,float vx,float vy, float radius):
    m_pos(x,y),m_v(vx,vy),m_radius(radius)
{
    m_circle.setRadius(radius);
    m_circle.setOrigin(sf::Vector2f(radius, radius));
}

Rock::~Rock()
{

}

void Rock::draw(sf::RenderWindow &window)
{
    
    m_circle.setPosition(m_pos);
    window.draw(m_circle);
}

void Rock::updatePosition()
{
    //--
    m_pos += m_v;

}

void Rock::setVelocity(float vx,float vy)
{
    m_v.x = vx;
    m_v.y = vy;
}

float Rock::left()
{
    return m_pos.x - m_radius;
}

float Rock::right()
{
    return m_pos.x + m_radius;
}

float Rock::top()
{
    return m_pos.y - m_radius;
}

float Rock::bottom()
{
    return m_pos.y + m_radius;
}
