//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Rectangle.cpp                             //
//            █ █        █ █        Lore                                      //
//             ████████████                                                   //
//           █              █       Copyright (c) 2016                        //
//          █     █    █     █      AmazingCow - www.AmazingCow.com           //
//          █     █    █     █                                                //
//           █              █       N2OMatt - n2omatt@amazingcow.com          //
//             ████████████         www.amazingcow.com/n2omatt                //
//                                                                            //
//                  This software is licensed as GPLv3                        //
//                 CHECK THE COPYING FILE TO MORE DETAILS                     //
//                                                                            //
//    Permission is granted to anyone to use this software for any purpose,   //
//   including commercial applications, and to alter it and redistribute it   //
//               freely, subject to the following restrictions:               //
//                                                                            //
//     0. You **CANNOT** change the type of the license.                      //
//     1. The origin of this software must not be misrepresented;             //
//        you must not claim that you wrote the original software.            //
//     2. If you use this software in a product, an acknowledgment in the     //
//        product IS HIGHLY APPRECIATED, both in source and binary forms.     //
//        (See opensource.AmazingCow.com/acknowledgment.html for details).    //
//        If you will not acknowledge, just send us a email. We'll be         //
//        *VERY* happy to see our work being used by other people. :)         //
//        The email is: acknowledgment_opensource@AmazingCow.com              //
//     3. Altered source versions must be plainly marked as such,             //
//        and must not be misrepresented as being the original software.      //
//     4. This notice may not be removed or altered from any source           //
//        distribution.                                                       //
//     5. Most important, you must have fun. ;)                               //
//                                                                            //
//      Visit opensource.amazingcow.com for more open-source projects.        //
//                                                                            //
//                                  Enjoy :)                                  //
//----------------------------------------------------------------------------//

//Header
#include "../include/Rectangle.h"
//Lore
#include "../include/SDLHelpers.h"

//Usings
USING_NS_LORE

// Static Methods //
const Rectangle& Rectangle::Empty()
{
    static Rectangle s_emptyRect;
    return s_emptyRect;
}

const Rectangle& Rectangle::Unit()
{
    static Rectangle s_unitRect(1, 1, 1, 1);
    return s_unitRect;
}


// CTOR / DTOR //
Rectangle::Rectangle() :
    Rectangle(0, 0, 0, 0)
{
    //Empty...
}

Rectangle::Rectangle(float x, float y, float w, float h) :
    Rectangle(Vector2(x, y), Vector2(w, h))
{
    //Empty...
}

Rectangle::Rectangle(const Vector2 &pos, const Vector2 &size) :
    m_position(pos),
    m_size    (size)
{
    //Empty...
}


// Public Methods //
//
void  Rectangle::setX(float x)
{
    m_position.setX(x);
}
float Rectangle::getX() const
{
    return m_position.getX();
}

void  Rectangle::setY(float y)
{
    m_position.setY(y);
}
float Rectangle::getY() const
{
    return m_position.getY();
}

void  Rectangle::setWidth(float w)
{
    m_size.setX(w);
}
float Rectangle::getWidth() const
{
    return m_size.getX();
}

void  Rectangle::setHeight(float h)
{
    m_size.setY(h);
}
float Rectangle::getHeight() const
{
    return m_size.getY();
}


//Left
float Rectangle::getLeft() const
{
    return m_position.x;
}

Vector2 Rectangle::getTopLeft() const
{
    return m_position;
}

Vector2 Rectangle::getMiddleLeft() const
{
    return Vector2(m_position.x, getBottom() / 2);
}

Vector2 Rectangle::getBottomLeft() const
{
    return Vector2(m_position.x, getBottom());
}

//Right
float Rectangle::getRight() const
{
    return m_position.x + m_size.x;
}

Vector2 Rectangle::getTopRight() const
{
    return Vector2(getRight(), m_position.y);
}

Vector2 Rectangle::getMiddleRight() const
{
    return Vector2(getRight(), getBottom() / 2);
}

Vector2 Rectangle::getBottomRight() const
{
    return Vector2(getRight(), getBottom());
}

//Top
float Rectangle::getTop() const
{
    return m_position.y;
}

//Bottom
float Rectangle::getBottom() const
{
    return m_position.y + m_size.y;
}

//Center
Vector2 Rectangle::getCenter() const
{
    return Vector2(getRight() / 2, getBottom() / 2);
}


//
void Rectangle::setLocation(const Vector2 &pos)
{
    m_position = pos;
}
const Vector2& Rectangle::getLocation() const
{
    return m_position;
}

void Rectangle::setSize(const Vector2 &size)
{
    m_size = size;
}
const Vector2& Rectangle::getSize() const
{
    return m_size;
}

//
bool Rectangle::isEmpty()
{
    return (*this) == Rectangle::Empty();
}
bool Rectangle::isUnit()
{
    return (*this) == Rectangle::Unit();
}


// Query Methods //
bool Rectangle::intersects(const Rectangle &that)
{
    return that.getLeft () < this->getRight () &&
           this->getLeft() < that.getRight  () &&
           that.getTop  () < this->getBottom() &&
           this->getTop () < that.getBottom ();
}

bool Rectangle::intersectionRect(const Rectangle &otherRect,
                                 Rectangle &outRect)
{
    //COWTODO: This is very ugly... just a quick hack to keep the \
    //         the Game_Frogger going... IMPLEMENT THIS CORRECTLY.
    auto a = SDLHelpers::make_rect(*this);
    auto b = SDLHelpers::make_rect(otherRect);
    SDL_Rect o;

    auto ret = SDL_IntersectRect(&a, &b, &o);
    outRect = Rectangle(o.x, o.y, o.w, o.h);

    return ret;
}


// Operators //
NS_LORE_BEGIN
bool operator ==(const Rectangle &lhs, const Rectangle &rhs)
{
    return lhs.getLocation() == rhs.getLocation() &&
           lhs.getSize()     == rhs.getSize();
}
bool operator !=(const Rectangle &lhs, const Rectangle &rhs)
{
    return !(lhs == rhs);
}
NS_LORE_END
