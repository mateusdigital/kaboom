//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        SDLHelper.h                               //
//            █ █        █ █        Lore                                      //
//             ████████████                                                   //
//           █              █       Copyright (c) 2016, 2017                  //
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

#ifndef __Lore_include_SDLHelpers_h__
#define __Lore_include_SDLHelpers_h__

//std
#include <string>
//Lore
#include "Lore_Utils.h"
#include "Color.h"
#include "Rectangle.h"
#include "Vector2.h"


NS_LORE_BEGIN
namespace SDLHelpers {

// Point //
SDL_Point make_point(int x, int y);
SDL_Point make_point(const Vector2 &vector);
SDL_Point make_point(const Rectangle &rect);

// Rectangle //
SDL_Rect make_rect(int x, int y, int w, int h);
SDL_Rect make_rect(const Vector2 &pos, const Vector2 &size);
SDL_Rect make_rect(const Rectangle &rect);

// Color //
SDL_Color make_color(int r, int g, int b, int a = 255);
SDL_Color make_color(const Color &color);

// Texture //
SDL_Texture* load_texture_from_file(const std::string &filename);
SDL_Texture* make_texture_free(SDL_Surface *surface);
SDL_Texture* make_texture_empty(int width = 1, int height = 1);

// Surface //
SDL_Surface* load_surface_from_file(const std::string &filename);

// Font //
TTF_Font* load_font_from_file(const std::string &filename, int size);

// Message Box //
void MessageBox_Error(const std::string &title, const std::string &msg);

}; //namespace SDLHelpers
NS_LORE_END
#endif // __Lore_include_SDLHelpers_h__ //
