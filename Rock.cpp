#include <SFML/Graphics/Color.hpp>
#include <math.h>
#include "Rock.h"
#include "RVector2D.h"
#include <SFML/System/Vector2.hpp>

Rock::Rock(float x,float y,float vx,float vy, float radius):
    m_pos(x,y),m_v(vx,vy),m_radius(radius)
{
    m_circle.setRadius(radius);
    m_circle.setOrigin(sf::Vector2f(radius, radius));

    updateUnitVectors();

}

Rock::~Rock()
{

}

void Rock::draw(sf::RenderWindow &window)
{
    
    m_circle.setPosition(m_pos);
    m_circle.setFillColor(sf::Color(200,200,0));
    window.draw(m_circle);

    sf::VertexArray line(sf::LinesStrip,2);
    line[0].position = m_pos;
    line[0].color = sf::Color::Red;
    sf::Vector2f v = m_pos + 30.0f*m_uv;
    line[1].position = v;
    line[1].color = sf::Color::White;
    window.draw(line);

    line[0].position = m_pos;
    line[0].color = sf::Color::Blue;
    v = m_pos + 30.0f*m_un;
    line[1].position = v;
    line[1].color = sf::Color::White;
    window.draw(line);

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

    updateUnitVectors();

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

void Rock::updateUnitVectors()
{
   //-----------------------------------
    m_uv = m_v.unitVector();
    m_un = m_uv.normalVector();

}
