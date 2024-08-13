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


    friend RVector2D operator+(RVector2D A, const RVector2D& B)
    {
        return A+=B;
    }

    RVector2D&  operator+=(const RVector2D& B)
    {
        static_cast<sf::Vector2<float>&>(*this) += B;
        return *this;
    }

    friend RVector2D operator-(RVector2D A, const RVector2D& B)
    {
        return A-=B;
    }

    RVector2D&  operator-=(const RVector2D& B)
    {
        static_cast<sf::Vector2<float>&>(*this) -= B;
        return *this;
    }

    friend RVector2D operator*(float left,const RVector2D &right)
    {
        return RVector2D(left*right.x,left*right.y);
    }

    friend RVector2D operator*(const RVector2D &left,float right)
    {
        return RVector2D(right*left.x,right*left.y);
    }

    // Dot product
    friend float operator*(const RVector2D& A, const RVector2D& B)
    {
        return A.x*B.x + A.y*B.y;
    }

    float distance(const RVector2D &a);

    static float distance(const RVector2D &a, const RVector2D &b);

};