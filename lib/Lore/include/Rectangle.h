//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Rectangle.h                               //
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

#ifndef __Lore_include_Rectangle_h__
#define __Lore_include_Rectangle_h__

//Lore
#include "Lore_Utils.h"
#include "Vector2.h"


NS_LORE_BEGIN

class Rectangle
{
    // Static Methods //
public:
    static const Rectangle& Empty();
    static const Rectangle& Unit ();


    // CTOR / DTOR //
public:
    Rectangle();
    Rectangle(float x, float y, float w, float h);
    Rectangle(const Vector2 &pos, const Vector2 &size);


    // Public Methods //
public:
    //
    void  setX(float x);
    float getX() const;

    void  setY(float y);
    float getY() const;

    void  setWidth(float w);
    float getWidth() const;

    void  setHeight(float h);
    float getHeight() const;

    //////////////////////////////////////////
    //                Top                   //
    //         TL            TR             //
    //            +---------+               //
    //            |         |               //
    //    Left ML |    C    | MR  Right     //
    //            |         |               //
    //            +---------+               //
    //         BL            BR             //
    //              Bottom                  //
    //////////////////////////////////////////
    //Left
    float   getLeft      () const;
    Vector2 getTopLeft   () const;
    Vector2 getMiddleLeft() const;
    Vector2 getBottomLeft() const;
    //Right
    float   getRight      () const;
    Vector2 getTopRight   () const;
    Vector2 getMiddleRight() const;
    Vector2 getBottomRight() const;
    //Top
    float getTop() const;
    //Bottom
    float getBottom() const;
    //Center
    Vector2 getCenter() const;


    //
    void setLocation(const Vector2 &pos);
    const Vector2& getLocation() const;

    void setSize(const Vector2 &size);
    const Vector2& getSize() const;

    //
    bool isEmpty();
    bool isUnit();


    // Query Methods //
public:
    bool intersects(const Rectangle &otherRect);
    bool intersectionRect(const Rectangle &otherRect,
                          Rectangle &outRect);

    // Operators //
public:
    //COWTODO: Add the operators.
    friend bool operator ==(const Rectangle &lhs, const Rectangle &rhs);
    friend bool operator !=(const Rectangle &lhs, const Rectangle &rhs);


    // iVars //
private:
    Vector2 m_position;
    Vector2 m_size;
};

NS_LORE_END
#endif // __Lore_include_Rectangle_h__ //
