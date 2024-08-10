#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "RVector.h"

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
    RVector computeNormal(RVector v);
    void updateUnitVectors();



    RVector     m_pos;
    RVector     m_v;
    RVector     m_un;
    RVector     m_uv;
    float       m_radius;
    sf::CircleShape m_circle;


};