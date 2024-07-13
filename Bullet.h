#pragma once
#include <SFML/Graphics.hpp>

class Bullet{
public:
    Bullet(float x,float y,float nx,float ny);
    ~Bullet();
    void updatePos();
    void draw(sf::RenderWindow &window);

    sf::Vector2f m_pos;
    sf::Vector2f m_n; 

    bool    m_f_deleted;

};
