#include <SFML/Graphics/Color.hpp>
#include <iostream>
#include <math.h>
#include "Rock.h"
#include "RVector2D.h"
#include <SFML/System/Vector2.hpp>
#include <ostream>

Rock::Rock(float x,float y,float vx,float vy, float mass):
    m_pos(x,y),m_v(vx,vy),m_mass(mass)
{
    m_radius = 10.0*m_mass;
    m_circle.setRadius(m_radius);
    m_circle.setOrigin(sf::Vector2f(m_radius, m_radius));

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


bool Rock::collision(const Rock &r)
{
    float d = RVector2D::distance(m_pos, r.m_pos);
    if (d<=(m_radius+r.m_radius)){
        std::cout << "Collision" << std::endl;
        return true;
    }
    return false;
}