//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Clock.cpp                                 //
//            █ █        █ █        CoreClock                                 //
//             ████████████                                                   //
//           █              █       Copyright (c) 2015, 2016                  //
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
#include "../include/Clock.h"

//Usings
USING_NS_CORECLOCK;

////////////////////////////////////////////////////////////////////////////////
// Constants / Enums / Typedefs                                               //
////////////////////////////////////////////////////////////////////////////////
const int Clock::kRepeatForever = -1;


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
Clock::Clock() :
    Clock(0)
{
    //Empty...
}

Clock::Clock(float interval) :
    Clock(interval, Clock::kRepeatForever)
{
    //Empty...
}

Clock::Clock(float interval, int repeat):
    Clock(interval,
          repeat,
          Callback(), //Tick
          Callback()) //Done
{
    //Empty...
}

Clock::Clock(float interval,
             const Callback &tickCallback,
             const Callback &doneCallback /* = Callback() */ ) :
    Clock(interval,
          Clock::kRepeatForever,
          tickCallback,
          doneCallback)
{
    //Empty...
}

Clock::Clock(float interval,
             int repeat,
             const Callback &tickCallback,
             const Callback &doneCallback /* = Callback() */) :
    m_interval    (interval),
    m_repeatCount (repeat),
    m_tickCount   (0),
    m_tickCallback(tickCallback),
    m_doneCallback(doneCallback),
    m_enabled     (false),
    m_updateTime  (interval)
{
    //Empty...
}


Clock::~Clock()
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Action Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
void Clock::start()
{
    m_tickCount = 0;

    m_enabled    = true;
    m_updateTime = m_interval;
}

void Clock::stop()
{
    m_enabled = false;
}


void Clock::update(float dt)
{
    if(!m_enabled)
        return;

    if(m_repeatCount != Clock::kRepeatForever && m_tickCount >= m_repeatCount)
        return;

    m_updateTime -= dt;
    if(m_updateTime <= 0)
    {
        m_updateTime = m_interval;
        ++m_tickCount;

        if(m_tickCallback)
            m_tickCallback();

        if(m_tickCount == m_repeatCount && m_doneCallback)
            m_doneCallback();
    }
}


////////////////////////////////////////////////////////////////////////////////
// Interval Methods                                                           //
////////////////////////////////////////////////////////////////////////////////
void Clock::setInterval(float interval)
{
    m_interval = interval;
}

float Clock::getInterval() const
{
    return m_interval;
}


////////////////////////////////////////////////////////////////////////////////
// Repeat Count Methods                                                       //
////////////////////////////////////////////////////////////////////////////////
void Clock::setRepeatCount(int count)
{
    m_repeatCount = count;
}
int Clock::getRepeatCount() const
{
    return m_repeatCount;
}


////////////////////////////////////////////////////////////////////////////////
// Tick Count / Query Methods                                                 //
////////////////////////////////////////////////////////////////////////////////
int Clock::getTickCount() const
{
    return m_tickCount;
}

bool Clock::isDone() const
{
    return m_tickCount == m_repeatCount;
}


////////////////////////////////////////////////////////////////////////////////
// Callback Methods                                                           //
////////////////////////////////////////////////////////////////////////////////
void Clock::setTickCallback(const Callback &callback)
{
    m_tickCallback = callback;
}

const Clock::Callback& Clock::getTickCallback() const
{
    return m_tickCallback;
}

void Clock::setDoneCallback(const Callback &callback)
{
    m_doneCallback = callback;
}

const Clock::Callback& Clock::getDoneCallback() const
{
    return m_doneCallback;
}
