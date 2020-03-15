//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        SoundManager.cpp                          //
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
#include "../include/SoundManager.h"
//Lore
#include "../include/AssetsManager.h"
#include "../include/ErrorControl.h"
//Lore_Private
#include "./private/include/Lore_Private_Utils.h"
#include "./private/include/Log.h"

//Usings
USING_NS_LORE;
USING_NS_COREGAME;


////////////////////////////////////////////////////////////////////////////////
// Constants                                                                  //
////////////////////////////////////////////////////////////////////////////////
//Class
const int SoundManager::kPlayForever = -1;
const int SoundManager::kPlayOneTime =  0;

//Get the values directly from SDL.
const int SoundManager::kDefaultFrequency = MIX_DEFAULT_FREQUENCY;
const int SoundManager::kDefaultFormat    = MIX_DEFAULT_FORMAT;
const int SoundManager::kDefaultChannels  = MIX_DEFAULT_CHANNELS;
const int SoundManager::kDefaultChunkSize = 4096;


//Internal
constexpr int   kMIX_FirstAvailableChannel = -1;
constexpr int   kMIX_AllChannels           = -1;
constexpr float kMIX_MaxVolume             = 128.0;
constexpr int   kMIX_GetVolume             = -1;


////////////////////////////////////////////////////////////////////////////////
// Init / Shutdown                                                            //
////////////////////////////////////////////////////////////////////////////////
void SoundManager::initialize(int    frequency,
                              Uint16 format,
                              int    channels,
                              int    chunksize)

{
    //Only initialize SDL_Audio if it wasn't initialized yet...
    if(SDL_WasInit(SDL_INIT_AUDIO) != 0)
    {
        if(SDL_Init(SDL_INIT_AUDIO) < 0)
        {
            ErrorControl::DieIfNeeded(
                ErrorControl::LORE_ERROR_DIE_ON_SOUND_MANAGER_ERROR |
                ErrorControl::LORE_ERROR_DIE_ON_SDL_ERROR,
                "SoundManager::initialize",
                "SDL Audio cannot be initialized - SDL error %s",
                SDL_GetError()
            );
        }
    }

    //Open the Mixer Audio.
    //COWTODO: Investigate a bug that is messing everything \
    //         if this function wasn't called.
    Mix_SetSoundFonts(nullptr);

    if(Mix_OpenAudio(frequency, format, channels, chunksize) < 0)
    {
        ErrorControl::DieIfNeeded(
                ErrorControl::LORE_ERROR_DIE_ON_SOUND_MANAGER_ERROR |
                ErrorControl::LORE_ERROR_DIE_ON_SDL_ERROR,
                "SoundManager::initialize",
                "SDL_Mixer cannot be initialized - Mixer error %s",
                Mix_GetError()
        );
    }

    m_muted = false;
}

void SoundManager::shutdown()
{
    Mix_CloseAudio();
    //COWTODO: DO the correct umload.
}


////////////////////////////////////////////////////////////////////////////////
// Volume Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
//Master
void SoundManager::setMasterVolume(float vol)
{
    PVT_LORE_DLOG_DEBUG(
        "SoundManager::setMasterVolume",
        "Setting Master Volume to %.2f", vol
    );

    setEffectsVolume(vol);
    setMusicVolume  (vol);
}

void SoundManager::toggleMute()
{
    m_muted = !m_muted;
}

bool SoundManager::isMuted() const
{
    return m_muted;
}

//Effect
void SoundManager::setEffectsVolume(float vol)
{
    PVT_LORE_DLOG_DEBUG(
        "SoundManager::setEffectsVolume",
        "Setting Effects Volume to %.2f", vol
    );

    COREGAME_ASSERT_ARGS(vol >= 0 && vol <= 1,
                         "Volume range is invalid (0, 1) - volume (%d)",
                         vol);

    Mix_Volume(kMIX_AllChannels, static_cast<int>(vol * kMIX_MaxVolume));
}

float SoundManager::getEffectsVolume() const
{
    return Mix_Volume(kMIX_AllChannels, kMIX_GetVolume) / kMIX_MaxVolume;
}


//Music
void SoundManager::setMusicVolume(float vol)
{
     PVT_LORE_DLOG_DEBUG(
        "SoundManager::setMusicVolume",
        "Setting Music Volume to %.2f", vol
    );

    COREGAME_ASSERT_ARGS(vol >= 0 && vol <= 1,
                         "Volume range is invalid (0, 1) - volume (%d)",
                         vol);

    Mix_VolumeMusic(static_cast<int>(vol * kMIX_MaxVolume));
}

float SoundManager::getMusicVolume() const
{
    return Mix_VolumeMusic(kMIX_GetVolume) / kMIX_MaxVolume;
}


////////////////////////////////////////////////////////////////////////////////
// Player Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
//Effects
void SoundManager::playEffect(const std::string &name,
                              int loopTimes /* = kPlayOneTime */)
{
    if(m_muted)
        return;

    auto fullname   = AssetsManager::instance()->fullpath(name);
    auto effectInfo = getEffectInfo(fullname);

    effectInfo.playChannel = Mix_PlayChannel(kMIX_FirstAvailableChannel,
                                             effectInfo.chunk,
                                             loopTimes);
}

void SoundManager::stopEffect(const std::string &name)
{
    auto fullname   = AssetsManager::instance()->fullpath(name);
    auto effectInfo = getEffectInfo(fullname);

    Mix_HaltChannel(effectInfo.playChannel);
}

void SoundManager::stopAllEffects()
{
    //COWTODO: Implement...
}

//Music
void SoundManager::playMusic(const std::string &name,
                             int loopTimes /* = kPlayForerver */)
{
    //COWTODO: Implement...
    PVT_LORE_UNUSED(name);
    PVT_LORE_UNUSED(loopTimes);

}

void SoundManager::stopMusic()
{

}


////////////////////////////////////////////////////////////////////////////////
// Load / Unload Methods                                                      //
////////////////////////////////////////////////////////////////////////////////
//Load
void SoundManager::loadEffect(const std::string &name)
{
    auto fullname = AssetsManager::instance()->fullpath(name);

    PVT_LORE_DLOG_DEBUG(
        "SoundManager::loadEffect",
        "Loading effect (%s)",
        fullname.c_str()
    );

    if(isEffectLoaded(fullname))
    {
        PVT_LORE_DLOG_WARNING(
            "SoundManager::loadEffect",
            "Trying to load a already load effect (%s)",
            fullname.c_str()
        );

        return;
    }

    auto effect = Mix_LoadWAV(fullname.c_str());
    if(!effect)
    {
        ErrorControl::DieIfNeeded(
            ErrorControl::LORE_ERROR_DIE_ON_SOUND_MANAGER_ERROR,
            "SoundManager::loadEffect",
            "Failed to load effect - EffectName: (%s) - Mix Error (%s)",
            fullname.c_str(),
            Mix_GetError()
        );
    }

    m_effectsMap[fullname] = EffectInfo { effect, -1 };
}

void SoundManager::loadMusic(const std::string &name)
{
    //COWTODO: Implement.
    PVT_LORE_UNUSED(name);
}

//Unload
void SoundManager::unloadEffect(const std::string &name)
{
    //COWTODO: Implement.
    PVT_LORE_UNUSED(name);
}

void SoundManager::unloadMusic(const std::string &name)
{
    //COWTODO: Implement.
    PVT_LORE_UNUSED(name);
}

//Query
bool SoundManager::isEffectLoaded(const std::string &name)
{
    return m_effectsMap.find(name) != std::end(m_effectsMap);
}

bool SoundManager::isMusicLoaded(const std::string &name)
{
    //COWTODO: Implement.
    PVT_LORE_UNUSED(name);
    return false;
}


////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
SoundManager::EffectInfo& SoundManager::getEffectInfo(const std::string &name)
{
    //COWTODO: Handle cases that effect isn't loaded.
    return m_effectsMap[name];
}
