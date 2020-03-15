//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        ITransformable.cpp                        //
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
#include "../include/ITransformable.h"
//Lore
#include "../include/AssetsManager.h"
//Lore Private
#include "./private/include/Lore_Private_Utils.h"

//Usings
USING_NS_LORE


////////////////////////////////////////////////////////////////////////////////
// Inner Types                                                                //
////////////////////////////////////////////////////////////////////////////////
const Vector2 ITransformable::OriginHelpers::TopLeft()
{
    static Vector2 s_topLeft(0, 0);
    return s_topLeft;
}

const Vector2 ITransformable::OriginHelpers::MiddleLeft()
{
    static Vector2 s_middleLeft(0, 0.5);
    return s_middleLeft;
}

const Vector2 ITransformable::OriginHelpers::BottomLeft()
{
    static Vector2 s_bottomLeft(0, 1);
    return s_bottomLeft;
}


const Vector2 ITransformable::OriginHelpers::TopCenter()
{
    static Vector2 s_topCenter(0.5, 0);
    return s_topCenter;
}

const Vector2 ITransformable::OriginHelpers::Center()
{
    static Vector2 s_center(0.5, 0.5);
    return s_center;
}

const Vector2 ITransformable::OriginHelpers::BottomCenter()
{
    static Vector2 s_bottomCenter(0.5, 1);
    return s_bottomCenter;
}


const Vector2 ITransformable::OriginHelpers::TopRight()
{
    static Vector2 s_topRight(1, 0);
    return s_topRight;
}

const Vector2 ITransformable::OriginHelpers::MiddleRight()
{
    static Vector2 s_middleRight(1, 0.5);
    return s_middleRight;
}

const Vector2 ITransformable::OriginHelpers::BottomRight()
{
    static Vector2 s_bottomRight(1, 1);
    return s_bottomRight;
}



////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
ITransformable::ITransformable() :
    m_position(Vector2::Zero()),
    m_rotation(0),
    m_scale   (Vector2::One()),
    m_origin  (Vector2::Zero())
{
    //Empty...
}
ITransformable::~ITransformable()
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
//Position
void ITransformable::setPosition(const Vector2 &position)
{
    m_position = position;
}
void ITransformable::setPosition(float x, float y)
{
    m_position.x = x;
    m_position.y = y;
}
void ITransformable::setPositionX(float x)
{
    m_position.x = x;
}
void ITransformable::setPositionY(float y)
{
    m_position.y = y;
}

const Vector2& ITransformable::getPosition() const
{
    return m_position;
}
float ITransformable::getPositionX() const
{
    return m_position.x;
}
float ITransformable::getPositionY() const
{
    return m_position.y;
}


//Rotation
void ITransformable::setRotation(float angle)
{
    m_rotation = angle;
}
float ITransformable::getRotation() const
{
    return m_rotation;
}


//Scale
void ITransformable::setScale(const Vector2 &scale)
{
    m_scale = scale;
}
void ITransformable::setScale(float x, float y)
{
    m_scale.x = x;
    m_scale.y = y;
}
void ITransformable::setScaleX(float x)
{
    m_scale.x = x;
}
void ITransformable::setScaleY(float y)
{
    m_scale.y = y;
}

const Vector2& ITransformable::getScale() const
{
    return m_scale;
}
float ITransformable::getScaleX() const
{
    return m_scale.x;
}
float ITransformable::getScaleY() const
{
    return m_scale.y;
}


//Origin
void ITransformable::setOrigin(const Vector2 &origin)
{
    COREGAME_ASSERT_ARGS(
        (origin.x >= 0 && origin.x <= 1) &&
        (origin.y >= 0 && origin.y <= 1),
        "ITransformable::setOrigin - Origin is out of range [0, 1] x: %.2f - y: %.2f",
        origin.x, origin.y
    );

    m_origin = origin;
}
void ITransformable::setOrigin(float x, float y)
{
    COREGAME_ASSERT_ARGS(
        (x >= 0 && x <= 1) &&
        (y >= 0 && y <= 1),
        "ITransformable::setOrigin - Origin is out of range [0, 1] x: %.2f - y: %.2f",
        x, y
    );

    m_origin.x = x;
    m_origin.y = y;
}
void ITransformable::setOriginX(float x)
{
    COREGAME_ASSERT_ARGS(
        (x >= 0 && x <= 1),
        "ITransformable::setOriginX - Origin is out of range [0, 1] x: %.2f",
        x
    );

    m_origin.x = x;
}
void ITransformable::setOriginY(float y)
{
    COREGAME_ASSERT_ARGS(
        (y >= 0 && y <= 1),
        "ITransformable::setOriginY - Origin is out of range [0, 1] y: %.2f",
        y
    );

    m_origin.y = y;
}

const Vector2& ITransformable::getOrigin() const
{
    return m_origin;
}
float ITransformable::getOriginX() const
{
    return m_origin.x;
}
float ITransformable::getOriginY() const
{
    return m_origin.y;
}


////////////////////////////////////////////////////////////////////////////////
// Transforms                                                                 //
////////////////////////////////////////////////////////////////////////////////
//Move
void ITransformable::move(const Vector2 &displacement)
{
    m_position += displacement;
}
void ITransformable::moveX(float x)
{
    m_position.x += x;
}
void ITransformable::moveY(float y)
{
    m_position.y += y;
}

//Rotate
void ITransformable::rotate(float angle)
{
    m_rotation += angle;
    if(m_rotation >= 360.0f)
        m_rotation -= 360.0f;
}

//Scale
void ITransformable::scale(const Vector2 factor)
{
    //COWTODO: Implement.
    PVT_LORE_UNUSED(factor);
}
void ITransformable::scale(float scale)
{
    //COWTODO: Implement.
    PVT_LORE_UNUSED(scale);
}
void ITransformable::scaleX(float x)
{
    //COWTODO: Implement.
    PVT_LORE_UNUSED(x);
}
void ITransformable::scaleY(float y)
{
    //COWTODO: Implement.
    PVT_LORE_UNUSED(y);
}
