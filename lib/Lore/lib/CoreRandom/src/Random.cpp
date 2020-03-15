//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Random.cpp                                //
//            █ █        █ █        CoreRandom                                //
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
#include "../include/Random.h"
//std
#include <cstdlib>
#include <limits>
#include <stdexcept>
#include <string>
#include <sstream>

//Usings.
USING_NS_CORERANDOM;


// Enums / Constants / Typdefs //
const int Random::kRandomSeed = -1;


// CTOR/DTOR //
Random::Random(int seed) :
    m_randomDist(0, 1)
{
    reseed(seed);
}


// Generation Methods //
int Random::next()
{
    resetRange(0, std::numeric_limits<int>::max());
    return m_dist(m_rnd);
}

int Random::next(int max)
{
    resetRange(0, max);
    return m_dist(m_rnd);
}

int Random::next(int min, int max)
{
    resetRange(min, max);
    return m_dist(m_rnd);
}

bool Random::nextBool()
{
    return static_cast<bool>(m_randomDist(m_rnd));
}


// Helper Methods //
Random::NumberGeneratorType&  Random::getNumberGenerator()
{
    return m_rnd;
}
const Random::NumberGeneratorType&  Random::getNumberGenerator() const
{
    return m_rnd;
}

Random::IntegerDistributionType&  Random::getIntDistribution()
{
    return m_dist;
}
const Random::IntegerDistributionType&  Random::getIntDistribution() const
{
    return m_dist;
}


void Random::reseed(int seed /* = kRandomSeed */)
{
    m_seed = (seed == Random::kRandomSeed)
              ? time(nullptr)
              : seed;

    m_isUsingRandomSeed = (seed == kRandomSeed);
    m_rnd.seed(m_seed);
}

int Random::getSeed() const
{
    return m_seed;
}

bool Random::isUsingRandomSeed() const
{
    return m_isUsingRandomSeed;
}



// Private Methods //
inline void Random::resetRange(int min, int max)
{
    if(min > max)
    {
        std::stringstream ss;
        ss << "CoreRandom::Random - Invalid range values - "
           << "min must be <= max - "
           << "Got min: " << min << " max: " << max;

        throw std::invalid_argument(ss.str());
    }


    if(m_dist.min() != min || m_dist.max() != max)
        m_dist.param(std::uniform_int_distribution<int>::param_type(min, max));
}
