//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        SDLHelper.cpp                             //
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

//Header
#include "../include/SDLHelpers.h"
//Lore
#include "../include/WindowManager.h"

#include <unistd.h>

//Usings
USING_NS_LORE

NS_LORE_BEGIN

////////////////////////////////////////////////////////////////////////////////
// Point                                                                      //
////////////////////////////////////////////////////////////////////////////////
SDL_Point SDLHelpers::make_point(int x, int y)
{
    return (SDL_Point){x, y};
}

SDL_Point SDLHelpers::make_point(const Vector2 &vector)
{
    return make_point(vector.x, vector.y);
}

SDL_Point SDLHelpers::make_point(const Rectangle &rect)
{
    return make_point(rect.getLocation());
}


////////////////////////////////////////////////////////////////////////////////
// Rectangle                                                                  //
////////////////////////////////////////////////////////////////////////////////
SDL_Rect SDLHelpers::make_rect(int x, int y, int w, int h)
{
    return (SDL_Rect){x, y, w, h};
}

SDL_Rect SDLHelpers::make_rect(const Vector2 &pos, const Vector2 &size)
{
    return make_rect(pos.x, pos.y, size.x, size.y);
}

SDL_Rect SDLHelpers::make_rect(const Rectangle &rect)
{
    return make_rect(rect.getLocation(), rect.getSize());
}


////////////////////////////////////////////////////////////////////////////////
// Color                                                                      //
////////////////////////////////////////////////////////////////////////////////
SDL_Color SDLHelpers::make_color(int r, int g, int b, int a /* = 255 */)
{
    //COWTODO: Check errors.
    COREGAME_ASSERT_ARGS((
        (r >= 0 && r <= 255) &&
        (g >= 0 && g <= 255) &&
        (b >= 0 && b <= 255) &&
        (a >= 0 && a <= 255)),
        "Color components are out of range: r:%d g:%d b:%d a:%d", r, g, b, a);


    //Cast to make the compiler happy.
    return (SDL_Color){ Uint8(r), Uint8(g), Uint8(b), Uint8(a) };
}

SDL_Color SDLHelpers::make_color(const Color &color)
{
    return make_color(color.r, color.g, color.b, color.a);
}


////////////////////////////////////////////////////////////////////////////////
// Texture                                                                    //
////////////////////////////////////////////////////////////////////////////////
SDL_Texture* SDLHelpers::load_texture_from_file(const std::string &filename)
{
    auto surface = IMG_Load(filename.c_str());

    // COREGAME_ASSERT_ARGS(
    //     surface != nullptr,
    //     "Cannot load surface with filename - %s - CWD: %s",
    //     filename.c_str(),
    //     get_current_dir_name()
    // );

    return make_texture_free(surface);
}

SDL_Texture* SDLHelpers::make_texture_free(SDL_Surface *surface)
{
    COREGAME_ASSERT(surface != nullptr,
                    "Surface cannot be null");

    auto renderer = WindowManager::instance()->getRenderer();

    auto texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    COREGAME_ASSERT(texture != nullptr,
                    "Failed to create texture");

    return texture;
}

SDL_Texture* SDLHelpers::make_texture_empty(int width  /* = 1 */,
                                            int height /* = 1 */)
{
    COREGAME_ASSERT_ARGS(
        width > 0 && height > 0,
        "SDLHelpers::make_texture_empty - Size values are invalid: %d, %d",
        width, height
    );

    //COWTODO: Check if this is the correct way to get             \
    //         an empty texture. i.e. We shouldn't check           \
    //         the renderer first to get the pixel format and all?
    auto renderer = WindowManager::instance()->getRenderer();
    auto texture = SDL_CreateTexture(renderer,
                                     SDL_PIXELFORMAT_RGBA8888,
                                     SDL_TEXTUREACCESS_STATIC,
                                     width, height);

    COREGAME_ASSERT_ARGS(
        texture != nullptr,
        "SDLHelpers::make_texture_empty - Failed to create texture with size: %d, %d - SDL_Error %s",
        width, height,
        SDL_GetError()
    );

    return texture;
}

////////////////////////////////////////////////////////////////////////////////
// Surface                                                                    //
////////////////////////////////////////////////////////////////////////////////
SDL_Surface* SDLHelpers::load_surface_from_file(const std::string &filename)
{
    return IMG_Load(filename.c_str());
}

////////////////////////////////////////////////////////////////////////////////
// Font                                                                       //
////////////////////////////////////////////////////////////////////////////////
TTF_Font* SDLHelpers::load_font_from_file(const std::string &filename, int size)
{
    auto font = TTF_OpenFont(filename.c_str(), size);

    COREGAME_ASSERT_ARGS(font != nullptr,
                         "Cannot load font with filename - %s - size - %d",
                         filename.c_str(), size);

    return font;
}

////////////////////////////////////////////////////////////////////////////////
// Message Box                                                                //
////////////////////////////////////////////////////////////////////////////////
void SDLHelpers::MessageBox_Error(
    const std::string &title,
    const std::string &msg)
{
    SDL_ShowSimpleMessageBox(
        SDL_MESSAGEBOX_ERROR,
        title.c_str(),
        msg.c_str  (),
        nullptr
    );
}
NS_LORE_END
