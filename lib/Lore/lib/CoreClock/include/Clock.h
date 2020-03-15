//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Clock.h                                   //
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

#ifndef __CoreClock_include_Clock_h__
#define __CoreClock_include_Clock_h__

//std
#include <functional>
//CoreClock
#include "CoreClock_Utils.h"


NS_CORECLOCK_BEGIN

class Clock
{
    // Constants / Enums / Typedefs //
public:
    ///@brief Makes the clock ticks forever.
    ///The stop control must be manually set.
    static const int kRepeatForever;

    //COWTODO: DOCUMENTATION IS OUTDATED.
    ///@brief Just to ease the typing the type.
    ///This is the signature of the function that will
    ///be called when the Clock's interval is reached.
    typedef std::function<void ()> Callback;


    // CTOR / DTOR //
public:
    //COWTODO: DOCUMENTATION IS OUTDATED.
    ///@brief Constructs the Clock as:
    ///  interval = 0.
    ///  repeat   = Clock::kRepeatForever.
    ///  callback = "none".
    ///The Clock must be started manually.
    ///@see Clock::setInterval(), Clock::setRepeatCount(),
    ///     Clock::setTickCallback().
    Clock();

    //COWTODO: DOCUMENTATION IS OUTDATED.
    ///@brief Constructs the Clock as:
    ///  interval = as given.
    ///  repeat   = Clock::kRepeatForever.
    ///  callback = "none".
    ///The Clock must be started manually.
    ///@param interval - A positive value.
    ///@warning No checks are made by the CTORs - Is the caller
    ///responsibility of give consistent and valid values.
    ///@see Clock::setInterval(), Clock::setRepeatCount(),
    ///     Clock::setTickCallback().
    Clock(float interval);

    //COWTODO: DOCUMENTATION IS OUTDATED.
    ///@brief Constructs the Clock as:
    ///  interval = as given.
    ///  repeat   = as given.
    ///  callback = "none".
    ///The Clock must be started manually.
    ///@param interval - A positive value.
    ///@param repeat   - A positive value or Clock::kRepeatForever.
    ///@warning No checks are made by the CTORs - Is the caller
    ///responsibility of give consistent and valid values.
    ///@see Clock::setInterval(), Clock::setRepeatCount(),
    ///     Clock::setTickCallback().
    Clock(float interval, int repeat);

    //COWTODO: DOCUMENTATION IS OUTDATED.
    ///@brief Constructs the Clock as:
    ///  interval = as given.
    ///  repeat   = Clock::kRepeatForever.
    ///  callback = as give.
    ///The Clock must be started manually.
    ///@param interval - A positive value.
    ///@param callback - The function that will be called when
    ///interval is reached.
    ///@warning No checks are made by the CTORs - Is the caller
    ///responsibility of give consistent and valid values.
    ///@see Clock::setInterval(), Clock::setRepeatCount(),
    ///     Clock::setTickCallback().
    Clock(float interval,
          const Callback &tickCallback,
          const Callback &doneCallback = Callback());

    //COWTODO: DOCUMENTATION IS OUTDATED.
    ///@brief Constructs the Clock with the given arguments.
    ///The Clock must be started manually.
    ///@param interval - A positive value.
    ///@param repeat   - A positive value or Clock::kRepeatForever.
    ///@param callback - The function that will be called when
    ///interval is reached.
    ///@warning No checks are made by the CTORs - Is the caller
    ///responsibility of give consistent and valid values.
    ///@see Clock::setInterval(), Clock::setRepeatCount(),
    ///     Clock::setTickCallback().
    Clock(float interval,
          int repeat,
          const Callback &tickCallback,
          const Callback &doneCallback = Callback());

    ///@brief DTOR.
    ~Clock();


    // Action Methods //
public:
    //COWTODO: DOCUMENTATION IS OUTDATED.
    ///@brief Starts the clock, i.e it will be enabled in Clock::update.
    ///If the current tick count is less the repeat count, the Clock will
    ///call the callback when the interval is reached.
    ///@note This will reset the Clock internal structure, so if you want
    ///to inspect the previous state of the object, you must do this before
    ///call the Clock::start() method.
    ///@see Clock::stop(), Clock::update(), Clock::getInterval(),
    ///     Clock::getRepeatCount(), Clock::getTickCallback().
    void start();

    //COWTODO: DOCUMENTATION IS OUTDATED.
    ///@brief Stops the clock, i.e it will not be enabled in Clock::update.
    ///@see Clock::start(), Clock::update(), Clock::getInterval(),
    ///     Clock::getRepeatCount(), Clock::getTickCallback().
    void stop();


    // Update Methods //
public:
    //COWTODO: DOCUMENTATION IS OUTDATED.
    ///@brief Updates the current amount of "time" (The unit is irrelevant, but
    ///must be consistent at the same object) and possibly fire the callback
    ///if the conditions are met, otherwise the update method is
    ///just a early return call.
    ///@note The callback is fired if:
    ///@note 1. Clock is enabled
    ///@note 2. Tick count is < than Repeat Count or Clock::kRepeatForever is set.
    ///@note 3 - Interval is reached - Pretty obvious.
    ///@note 4 - Callback is set     - Pretty obvious too.
    ///@see Clock::start(), Clock::stop(), Clock::getRepeatCount(),
    ///     Clock::getTickCount()
    void update(float dt);


    // Interval Methods //
public:
    //COWTODO: DOCUMENTATION IS OUTDATED.
    ///@brief Sets the interval (the unit is irrelevant, but must be consistent
    ///at the same object) time for the Clock.
    ///@param interval - A positive value.
    ///@see Clock::getInterval().
    void setInterval(float interval);

    ///@brief Gets the current interval.
    ///@returns The current interval.
    ///@see Clock::setInterval().
    float getInterval() const;


    // Repeat Count Methods //
public:
    ///@brief Sets the Repeat Count.
    ///When the Tick count is greater than the Repeat Count the update method
    ///will stop fire the callback.
    ///@param count - A positive value or Clock::kRepeatForever.
    ///@see Clock::getTickCount(), Clock::getRepeatCount().
    void setRepeatCount(int count);

    ///@brief Gets the current Repeat Count.
    ///@returns The current Repeat Count.
    ///@see Clock::getTickCount(), Clock::setRepeatCount().
    int getRepeatCount() const;



    // Tick Count / Query Methods //
public:
    ///@brief Gets the current Tick Count.
    ///@returns The current Tick Count.
    ///@see Clock::getRepeatCount().
    int getTickCount() const;


    //COWTODO: Add documentation.
    bool isDone() const;


    // Callback  Methods //
public:
    ///@brief Set the function that will be called we the
    ///conditions are met in Clock::update().
    ///@param callback - A valid callback function.
    void setTickCallback(const Callback &callback);

    ///@brief Gets the const ref for the callback.
    const Callback& getTickCallback() const;

    //COWTODO: Add documentation.
    void setDoneCallback(const Callback &callback);
    //COWTODO: Add documentation.
    const Callback& getDoneCallback() const;


    // iVars //
public:
    float m_interval;

    int m_repeatCount;
    int m_tickCount;

    Callback m_tickCallback;
    Callback m_doneCallback;

    bool  m_enabled;
    float m_updateTime;
};

NS_CORECLOCK_END
#endif // defined(__CoreClock_include_Clock_h__) //
