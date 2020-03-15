//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Vector2.h                                 //
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

#ifndef __Lore_include_Vector2_h__
#define __Lore_include_Vector2_h__

////////////////////////////////////////////////////////////////////////////////
// This class had heavily borrowed the implementation                         //
// ideias from the  MonoGame Vector2.cs file.                                 //
////////////////////////////////////////////////////////////////////////////////

//Lore
#include "Lore_Utils.h"


NS_LORE_BEGIN

class Vector2
{
    // Static Methods //
public:
    static const Vector2& Zero ();
    static const Vector2& One  ();
    static const Vector2& UnitX();
    static const Vector2& UnitY();

    static Vector2 OffsetBy(const Vector2 &source, float x, float y);

    // CTOR / DTOR //
public:
    explicit Vector2();
    explicit Vector2(float value);
    explicit Vector2(float x, float y);


    // Public Methods //
public:
    void  setX(float x);
    float getX() const;

    void  setY(float y);
    float getY() const;


    // Operators //
public:
    //COWTODO: Add the operators.
    //Friends
    //Comparisons
    friend bool operator ==(const Vector2 &lhs, const Vector2 &rhs);
    friend bool operator !=(const Vector2 &lhs, const Vector2 &rhs);

    //Add / Subtract - Vectors
    friend Vector2 operator +(const Vector2 &lhs, const Vector2 &rhs);
    friend Vector2 operator -(const Vector2 &lhs, const Vector2 &rhs);

    //Add / Subtract - Scalars
    friend Vector2 operator +(const Vector2 &lhs, float rhs);
    friend Vector2 operator -(const Vector2 &lhs, float rhs);

    friend Vector2 operator +(float lhs, const Vector2 &rhs);
    friend Vector2 operator -(float lhs, const Vector2 &rhs);

    //Multiply / Divide - Vectors
    friend Vector2 operator *(const Vector2 &lhs, const Vector2 &rhs);
    friend Vector2 operator /(const Vector2 &lhs, const Vector2 &rhs);

    //Multiply / Divide - Scalars
    friend Vector2 operator *(const Vector2 &lhs, float rhs);
    friend Vector2 operator /(const Vector2 &lhs, float rhs);

    friend Vector2 operator *(float lhs, const Vector2 &rhs);
    friend Vector2 operator /(float lhs, const Vector2 &rhs);


    //Members
    //Add / Subtract - Vectors
    Vector2& operator +=(const Vector2 &rhs);
    Vector2& operator -=(const Vector2 &rhs);

    //Add / Subtract - Scalars
    Vector2& operator +=(float rhs);
    Vector2& operator -=(float rhs);

    //Multiply / Divide - Vectors
    Vector2& operator *=(const Vector2 &rhs);
    Vector2& operator /=(const Vector2 &rhs);

    //Multiply / Divide - Scalars
    Vector2& operator *=(float rhs);
    Vector2& operator /=(float rhs);


    // iVars //
public:
    float x, y;
};

NS_LORE_END
#endif // __Lore_include_Vector2_h__ //
