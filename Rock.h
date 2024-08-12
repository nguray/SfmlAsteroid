#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "RVector2D.h"

class Rock {
public:
    Rock(float x,float y,float vx,float vy,float mass);
    ~Rock();

    float left();
    float top();
    float right();
    float bottom();
    void  setVelocity(float vx,float vy);

    void updatePosition();
    void draw(sf::RenderWindow &window);
    void updateUnitVectors();
    bool collision(const Rock &r);

    RVector2D     m_pos;
    RVector2D     m_v;
    RVector2D     m_un;
    RVector2D     m_uv;
    float         m_mass;
    float         m_radius;
    sf::CircleShape m_circle;

};