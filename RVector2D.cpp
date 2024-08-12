
#include "RVector2D.h"
#include <SFML/System/Vector2.hpp>

RVector2D::RVector2D(float x, float y):sf::Vector2f(x,y)
{

}

// Get magnitude of vector
float RVector2D::magnitude(){
    return std::sqrt(x * x + y * y);
}

// Get a unit vector in the direction of this vector
// If this vector is the 0 vector, return a 0 vector
RVector2D RVector2D::unitVector(){
    double mag = magnitude();
    if (mag != 0.) 
        return RVector2D(x / mag, y / mag);
    else 
        return RVector2D();
}

RVector2D RVector2D::normalVector()
{
    return RVector2D( y,-x);
}

// Dot product
float RVector2D::operator*(const RVector2D &right)
{
    return (x * right.x + y * right.y);
}

// Distance
float RVector2D::distance(const RVector2D &a, const RVector2D &b)
{
    auto v = static_cast<sf::Vector2f>(a)-static_cast<sf::Vector2f>(b);
    return (RVector2D(v.x,v.y).magnitude());
}