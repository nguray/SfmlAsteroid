#pragma once
#include <iterator>
#include <math.h>
#include <SFML/System/Vector2.hpp>

class RVector2D : public sf::Vector2f 
{
public:
    RVector2D(float x=0.0f, float y=0.0f);

    float       magnitude();
    RVector2D   unitVector();
    RVector2D   normalVector();
    float       operator*(const RVector2D &right);

    static float distance(const RVector2D &a, const RVector2D &b);

};