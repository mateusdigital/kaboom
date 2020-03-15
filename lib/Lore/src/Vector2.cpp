//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Vector2.cpp                               //
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
#include "../include/Vector2.h"

//Usings
USING_NS_LORE

////////////////////////////////////////////////////////////////////////////////
// Static Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
const Vector2& Vector2::Zero()
{
    static Vector2 s_zeroRect;
    return s_zeroRect;
}

const Vector2& Vector2::One()
{
    static Vector2 s_oneRect(1, 1);
    return s_oneRect;
}

const Vector2& Vector2::UnitX()
{
    static Vector2 s_unitX(1, 0);
    return s_unitX;
}
const Vector2& Vector2::UnitY()
{
    static Vector2 s_unitY(0, 1);
    return s_unitY;
}

Vector2 Vector2::OffsetBy(const Vector2 &source, float x, float y)
{
    return Vector2(source.x + x, source.y + y);
}


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
Vector2::Vector2() :
    Vector2(0, 0)
{
    //Empty...
}

Vector2::Vector2(float value) :
    Vector2(value, value)
{
    //Empty...
}

Vector2::Vector2(float x, float y) :
    x(x),
    y(y)
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
void Vector2::setX(float x)
{
    this->x = x;
}

float Vector2::getX() const
{
    return x;
}

void Vector2::setY(float y)
{
    this->y = y;
}

float Vector2::getY() const
{
    return y;
}

////////////////////////////////////////////////////////////////////////////////
// Operators                                                                  //
////////////////////////////////////////////////////////////////////////////////
//Friends
NS_LORE_BEGIN

//Comparisons
bool operator ==(const Vector2 &lhs, const Vector2 &rhs)
{
    return lhs.x == rhs.x &&
           lhs.y == rhs.y;
}

bool operator !=(const Vector2 &lhs, const Vector2 &rhs)
{
    return !(lhs == rhs);
}


//Add / Subtract - Vectors
Vector2 operator +(const Vector2 &lhs, const Vector2 &rhs)
{
    return Vector2(lhs.x + rhs.x,
                   lhs.y + rhs.y);
}

Vector2 operator -(const Vector2 &lhs, const Vector2 &rhs)
{
    return Vector2(lhs.x - rhs.x,
                   lhs.y - rhs.y);
}


//Add / Subtract - Scalars
Vector2 operator +(const Vector2 &lhs, float rhs)
{
    return Vector2(lhs.x + rhs,
                   lhs.y + rhs);
}

Vector2 operator -(const Vector2 &lhs, float rhs)
{
    return Vector2(lhs.x - rhs,
                   lhs.y - rhs);
}


Vector2 operator +(float lhs, const Vector2 &rhs)
{
    return Vector2(lhs + rhs.x,
                   lhs + rhs.y);
}

Vector2 operator -(float lhs, const Vector2 &rhs)
{
    return Vector2(lhs - rhs.x,
                   lhs - rhs.y);
}


//Multiply / Divide - Vectors
Vector2 operator *(const Vector2 &lhs, const Vector2 &rhs)
{
    return Vector2(lhs.x * rhs.x,
                   lhs.y * rhs.y);
}

Vector2 operator /(const Vector2 &lhs, const Vector2 &rhs)
{
    return Vector2(lhs.x / rhs.x,
                   lhs.y / rhs.y);
}


//Multiply / Divide - Scalars
Vector2 operator *(const Vector2 &lhs, float rhs)
{
    return Vector2(lhs.x * rhs,
                   lhs.y * rhs);
}

Vector2 operator /(const Vector2 &lhs, float rhs)
{
    float factor = 1.0f / rhs;
    return Vector2(lhs.x * factor,
                   lhs.y * factor);
}


Vector2 operator *(float lhs, const Vector2 &rhs)
{
    return Vector2(lhs * rhs.x,
                   lhs * rhs.y);
}

Vector2 operator /(float lhs, const Vector2 &rhs)
{
    float factor = 1.0f / lhs;
    return Vector2(rhs.x * factor,
                   rhs.y * factor);
}
NS_LORE_END


//Members
//Add / Subtract - Vectors
Vector2& Vector2::operator +=(const Vector2 &rhs)
{
    this->x += rhs.x;
    this->y += rhs.y;
    return (*this);
}

Vector2& Vector2::operator -=(const Vector2 &rhs)
{
    this->x -= rhs.x;
    this->y -= rhs.y;
    return (*this);
}


//Add / Subtract - Scalars
Vector2& Vector2::operator +=(float rhs)
{
    this->x += rhs;
    this->y += rhs;
    return (*this);
}

Vector2& Vector2::operator -=(float rhs)
{
    this->x -= rhs;
    this->y -= rhs;
    return (*this);
}


//Multiply / Divide - Vectors
Vector2& Vector2::operator *=(const Vector2 &rhs)
{
    this->x *= rhs.x;
    this->y *= rhs.y;
    return (*this);
}

Vector2& Vector2::operator /=(const Vector2 &rhs)
{
    this->x /= rhs.x;
    this->y /= rhs.y;
    return (*this);
}


//Multiply / Divide - Scalars
Vector2& Vector2::operator *=(float rhs)
{
    this->x *= rhs;
    this->y *= rhs;
    return (*this);
}

Vector2& Vector2::operator /=(float rhs)
{
    this->x /= rhs;
    this->y /= rhs;
    return (*this);
}
