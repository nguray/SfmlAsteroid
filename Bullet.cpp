#include "Bullet.h"

Bullet::Bullet(float x,float y,float nx,float ny):
    m_pos(x,y),m_n(nx,ny),m_f_deleted(false)
{
    
}

Bullet::~Bullet()
{

}

void Bullet::updatePos()
{
    m_pos.x += m_n.x;
    m_pos.y += m_n.y;

}

void Bullet::draw(sf::RenderWindow &window)
{
    sf::VertexArray line(sf::LinesStrip,2);
    line[0].position = m_pos;
    line[0].color = sf::Color::Red;
    sf::Vector2f v = m_pos + 4.0f*m_n;
    line[1].position = v;
    line[1].color = sf::Color::White;
    window.draw(line);
}

