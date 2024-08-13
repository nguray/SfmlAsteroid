#include <math.h>
#include <filesystem>
#include <SFML/Graphics/VertexArray.hpp>
#include "MySprite.h"
#include <iostream>
#include <string>

MySprite::MySprite()
    :sf::Sprite(),m_pos(0.0,0.0),m_angle(0.0)
{
    setAngle(0.0);
}


MySprite::MySprite(float x, float y, float a)
    :sf::Sprite(),m_pos(x,y),
    m_n(0.0f,1.0f), m_Rad_Deg(M_PI/180.0f), 
    m_v(0.0f,0.0f)
{
    setAngle(a);
    std::filesystem::path resPath{".."};
    //std::cout << resPath/(std::string("Plan00") + ".png") << std::endl;
    m_Tex0.loadFromFile((resPath/"Plane00.png").string());
    m_Tex1.loadFromFile((resPath/"Plane01.png").string());
    m_Tex2.loadFromFile((resPath/"Plane02.png").string());
    setTexture(m_Tex0);
    setOrigin( 15.0f, 16.0f);

}

MySprite::~MySprite()
{

}

void MySprite::translate(float dx,float dy,float srcX,float srcY,float &desX,float &desY)
{
    desX = srcX + dx;
    desY = srcY + dy;
}

void MySprite::rotate(float degA, float srcX,float srcY,float &desX,float &desY)
{
    float   radA = degA * m_Rad_Deg;
    desX = srcX*cos(radA) - srcY*sin(radA);
    desY = srcX*sin(radA) + srcY*cos(radA);
}

void MySprite::createMask()
{
    const sf::Texture *tex = getTexture();
    sf::Image srcImg = tex->copyToImage();

    sf::Vector2f orig = getOrigin();

    sf::Vector2u s = srcImg.getSize();

    int iy = (int) orig.y;
    int ix = (int) orig.x;

    // Compute Mask size
    int d = s.y-iy;
    int ry = (iy>d?iy:d);
    d = s.x-ix;
    int rx = (ix>d?ix:d);
    int r = (rx>ry?rx:ry);

    m_mask.create(2*r,2*r,sf::Color(0,0,0,0));

    m_mask_dx = r - orig.x;
    m_mask_dy = r - orig.y;

    int minX=10000,maxX=-1;
    int minY=10000,maxY=-1;

    float x1,y1;
    float x2,y2;
    float x3,y3;
    sf::Color c;
    for(int y=0;y<s.y;y++){
        for(int x=0;x<s.x;x++){
            c = srcImg.getPixel(x,y);
            if (c.a!=0){
                translate( -orig.x, -orig.y, x, y, x1, y1);
                rotate( getRotation(), x1, y1, x2, y2);
                translate( orig.x, orig.y, x2, y2, x3, y3);
                x3 += m_mask_dx;
                y3 += m_mask_dy;
                if ((x3>=0)&&(x3<2*r)&&(y3>=0)&&(y3<2*r)){
                    m_mask.setPixel(x3,y3,c);
                    //-- Compute rect
                    if (x3<minX) minX = x3;
                    if (x3>maxX) maxX = x3;
                    if (y3<minY) minY = y3;
                    if (y3>maxY) maxY = y3;
                }
            }
        }
    }
    //-- Reel rect inside mask
    m_sub_mask_rect = sf::IntRect(minX,minY,maxX-minX+1,maxY-minY+1);

}

sf::IntRect MySprite::createMaskRect()
{
    sf::Vector2f o = getOrigin();
    sf::Vector2f p = getPosition();
    int l = p.x - o.x - m_mask_dx;
    int t  = p.y - o.y - m_mask_dy;
    sf::Vector2u s = m_mask.getSize();
    m_mask_rect = sf::IntRect(l,t,s.x,s.y);
    m_reduced_mask_rect = sf::IntRect(m_mask_rect.left+m_sub_mask_rect.left,
                            m_mask_rect.top+m_sub_mask_rect.top,
                            m_sub_mask_rect.width,m_sub_mask_rect.height);
    return m_mask_rect;
}

bool MySprite::collide(MySprite &sprite)
{
    //--------------------------------
    createMaskRect();

    sprite.createMaskRect();

    if (m_reduced_mask_rect.intersects(sprite.m_reduced_mask_rect,m_intersect_rect)){
        sprite.m_intersect_rect = m_intersect_rect;

        int maskX,maskY;
        sf::Color c;
        for (int y=m_intersect_rect.top;y<=(m_intersect_rect.top+m_intersect_rect.height);y++){
            for(int x=m_intersect_rect.left;x<=(m_intersect_rect.left+m_intersect_rect.width);x++){
                //-- Compute coordinate in internal Mask
                maskX = x - m_mask_rect.left;
                maskY = y - m_mask_rect.top;
                c = m_mask.getPixel(maskX,maskY);
                if (c.a!=0){
                    maskX = x - sprite.m_mask_rect.left;
                    maskY = y - sprite.m_mask_rect.top;
                    c = sprite.m_mask.getPixel(maskX,maskY);
                    if (c.a!=0){
                        return true;
                    }
                }
            }
        }

    }

    return false;
}

void MySprite::setAngle(float a)
{
    m_angle = a;
    m_n.x = cos( (a-90.0f) * m_Rad_Deg);
    m_n.y = sin( (a-90.0f) * m_Rad_Deg);
 
}

float MySprite::getAngle()
{
    return m_angle;
}

void MySprite::draw(sf::RenderWindow &window)
{
    setRotation(m_angle);
    setPosition(m_pos.x,m_pos.y);
    window.draw(*this);
}

void MySprite::accelerate()
{
    m_v += 0.005f * m_n;
    setTexture(m_Tex1);

}

void MySprite::idle()
{
    setTexture(m_Tex0);
    
}

void MySprite::decelerate()
{
    m_v -= 0.001f * m_n;
    setTexture(m_Tex2);    
}

void MySprite::updatePos()
{
    m_pos += m_v;
}

void MySprite::drawReducedMaskRect(sf::RenderWindow &window)
{
    //----------------------------------------
    sf::VertexArray lines(sf::LinesStrip, 5);
    float left = m_reduced_mask_rect.left;
    float top  = m_reduced_mask_rect.top;
    float right  = left + m_reduced_mask_rect.width;
    float bottom = top + m_reduced_mask_rect.height;
    lines[0].position = sf::Vector2f( left, top);
    lines[0].color = sf::Color::Red;
    lines[1].position = sf::Vector2f( right, top);
    lines[1].color = sf::Color::Red;
    lines[2].position = sf::Vector2f( right, bottom);
    lines[2].color = sf::Color::Red;
    lines[3].position = sf::Vector2f( left, bottom);
    lines[3].color = sf::Color::Red;
    lines[4].position = sf::Vector2f( left, top);
    lines[4].color = sf::Color::Red;
    window.draw(lines);
}

void MySprite::drawMaskRect(sf::RenderWindow &window)
{
    //----------------------------------------
    sf::VertexArray lines(sf::LinesStrip, 5);
    float left = m_mask_rect.left;
    float top  = m_mask_rect.top;
    float right  = left + m_mask_rect.width;
    float bottom = top + m_mask_rect.height;
    lines[0].position = sf::Vector2f( left, top);
    lines[0].color = sf::Color::Green;
    lines[1].position = sf::Vector2f( right, top);
    lines[1].color = sf::Color::Green;
    lines[2].position = sf::Vector2f( right, bottom);
    lines[2].color = sf::Color::Green;
    lines[3].position = sf::Vector2f( left, bottom);
    lines[3].color = sf::Color::Green;
    lines[4].position = sf::Vector2f( left, top);
    lines[4].color = sf::Color::Green;
    window.draw(lines);
}
