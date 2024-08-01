#pragma once
#include <SFML/Graphics.hpp>

class Rock {
public:
    Rock(float x,float y,float vx,float vy,float radius);
    ~Rock();

    float left();
    float top();
    float right();
    float bottom();
    void  setVelocity(float vx,float vy);

    void updatePosition();
    void draw(sf::RenderWindow &window);



    sf::Vector2f m_pos;
    sf::Vector2f m_v;
    float        m_radius;
    sf::CircleShape m_circle;


};