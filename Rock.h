#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

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
    void normalize(sf::Vector2f &v);
    sf::Vector2f computeNormal(sf::Vector2f v);
    void updateUnitVectors();



    sf::Vector2f m_pos;
    sf::Vector2f m_v;
    sf::Vector2f m_un;
    sf::Vector2f m_uv;
    float        m_radius;
    sf::CircleShape m_circle;


};