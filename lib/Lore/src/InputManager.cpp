//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        InputManager.cpp                          //
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
#include "../include/InputManager.h"
//std
#include <cstring>
#include <algorithm>

//Usings
USING_NS_LORE;


////////////////////////////////////////////////////////////////////////////////
// Init / Shutdown                                                            //
////////////////////////////////////////////////////////////////////////////////
void InputManager::initialize()
{
    m_pCurrKeys = const_cast<Uint8 *>(SDL_GetKeyboardState(&m_numKeys));
    m_pPrevKeys = new Uint8[m_numKeys];
}

void InputManager::shutdown()
{
    delete m_pPrevKeys;
}


////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
void InputManager::update()
{
    std::memcpy(m_pPrevKeys, m_pCurrKeys, sizeof(Uint8) * m_numKeys);
    m_pCurrKeys = const_cast<Uint8 *>(SDL_GetKeyboardState(nullptr));
}


////////////////////////////////////////////////////////////////////////////////
// Key "atomics" methods                                                      //
////////////////////////////////////////////////////////////////////////////////
bool InputManager::isKeyDown(KeyScanCodeType scanCode)
{
    return m_pCurrKeys[scanCode];
}

bool InputManager::isKeyUp(KeyScanCodeType scanCode)
{
    return !m_pCurrKeys[scanCode];
}


bool InputManager::wasKeyDown(KeyScanCodeType scanCode)
{
    return m_pPrevKeys[scanCode] && isKeyUp(scanCode);
}

bool InputManager::wasKeyUp(KeyScanCodeType scanCode)
{
    return !m_pPrevKeys[scanCode] && isKeyDown(scanCode);
}


bool InputManager::isKeyClick(KeyScanCodeType scanCode)
{
    return isKeyUp(scanCode) && wasKeyDown(scanCode);
}


////////////////////////////////////////////////////////////////////////////////
// Key bindings methods                                                       //
////////////////////////////////////////////////////////////////////////////////
void InputManager::assignKeyBindings(
    const std::string             &keybinding,
    const KeyScanCodeTypeInitList &keys)
{
    COREGAME_ASSERT(
        keys.size() != 0,
        "Keys cannot be empty"
    );

    m_keybindingsMap[keybinding].insert(keys);
}

//Empty list means that is to remove all bidings.
void InputManager::removeKeyBindings(
    const std::string &keybinding,
    const std::initializer_list<KeyScanCodeType> &keys)
{
    //COWTODO: implement...
}

template <typename PREDICATE_T>
bool TEST(
    const std::string                  &keybinding,
    InputManager::KeybindingsMap &keymap,
    PREDICATE_T predicate)
{
     //Check it keybinding valid.
    COREGAME_ONLY_IN_DEBUG({
        auto it = keymap.find(keybinding);
        COREGAME_ASSERT_ARGS(
            it != keymap.end(),
            "Keybinding (%s) was not found.",
            keybinding.c_str()
        );
    });

    const auto &keys_set = keymap[keybinding];
    return std::any_of(
        keys_set.begin(),
        keys_set.end  (),
        predicate
    );
}

bool InputManager::isKeyDown(const std::string &keybinding)
{
    return TEST(
        keybinding,
        m_keybindingsMap,
         [this](const KeyScanCodeType &keyCode){
            return isKeyDown(keyCode);
        }
    );
}

bool InputManager::isKeyUp(const std::string &keybinding)
{
    return TEST(
        keybinding,
        m_keybindingsMap,
         [this](const KeyScanCodeType &keyCode){
            return isKeyUp(keyCode);
        }
    );
}


bool InputManager::wasKeyDown(const std::string &keybinding)
{
    return TEST(
        keybinding,
        m_keybindingsMap,
         [this](const KeyScanCodeType &keyCode){
            return wasKeyDown(keyCode);
        }
    );
}

bool InputManager::wasKeyUp(const std::string &keybinding)
{
    return TEST(
        keybinding,
        m_keybindingsMap,
         [this](const KeyScanCodeType &keyCode){
            return wasKeyUp(keyCode);
        }
    );
}

bool InputManager::isKeyClick(const std::string &keybinding)
{
    return TEST(
        keybinding,
        m_keybindingsMap,
         [this](const KeyScanCodeType &keyCode){
            return isKeyClick(keyCode);
        }
    );
}
