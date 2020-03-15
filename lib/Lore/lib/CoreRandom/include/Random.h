//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Random.h                                  //
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

#ifndef __CoreRandom_include_Random_h__
#define __CoreRandom_include_Random_h__

//std
#include <random>
//CoreRandom
#include "CoreRandom_Utils.h"

NS_CORERANDOM_BEGIN

class Random
{
    // Enums / Constants / Typedefs //
public:
    ///@brief A meta value to indicate to Random()
    ///that it should use a random seed.
    ///@see Random(), getSeed(), isUsingRandomSeed().
    static const int kRandomSeed;

    ///@brief Typedef to reduce verbosity.
    typedef std::mt19937                       NumberGeneratorType;
    ///@brief Typedef to reduce verbosity.
    typedef std::uniform_int_distribution<int> IntegerDistributionType;


    // CTOR/DTOR //
public:
    ///@brief Constructs a Random object with the target seed.
    ///@param seed - The seed that the random number generator will
    ///be initialized. If seed is kRandomSeed it will be
    ///selected from the system std::time(nullptr).
    ///@see kRandomSeed, reseed(), getSeed(), isUsingRandomSeed().
    Random(int seed = kRandomSeed);


    // Generation Methods //
public:
    ///@brief Generate a random integer between [0, std::numeric_limits<int>::max()].
    ///@returns An integer in [0, std::numeric_limits<int>::max()] range.
    ///@note next return is INCLUSIVE.
    ///@see next(int max), next(int min, int max);
    int next();

    ///@brief Generate a random integer between [0, max].
    ///@param max - The upperbound of the range.
    ///@warning max must be >= 0.
    ///@returns An integer in [0, max] range.
    ///@throws std::invalid_argument if max < 0.
    ///@note next return is INCLUSIVE.
    ///@see next(), next(int min, int max);
    int next(int max);

    ///@brief Generate a random integer between [min, max].
    ///@param min - The lowerbound of the range.
    ///@param max - The upperbound of the range.
    ///@warning max >= min.
    ///@returns An integer in [min, max] range.
    ///@throws std::invalid_argument if max < min.
    ///@note next return is INCLUSIVE.
    ///@see next(), next(int max);
    int next(int min, int max);


    ///@brief Generate a random bool value.
    ///@returns A bool value.
    ///@see next(), next(int max), next(int min, int max);
    bool nextBool();


    // Helper Methods //
public:
    ///@brief Gets the reference for the internal number generator.
    ///@returns A reference for the internal number generator.
    ///@see NumberGeneratorType.
    NumberGeneratorType& getNumberGenerator();
    ///@brief Gets the constant reference for the internal number generator.
    ///@returns A constant reference for the internal number generator.
    ///@see NumberGeneratorType.
    const NumberGeneratorType& getNumberGenerator() const;

    ///@brief Gets the reference for the internal integer distribution.
    ///@returns A reference for the internal integer distribution.
    ///@see IntegerDistributionType.
    IntegerDistributionType& getIntDistribution();
    ///@brief Gets the constant reference for the internal integer distribution.
    ///@returns A constant reference for the internal integer distribution.
    ///@see IntegerDistributionType.
    const IntegerDistributionType& getIntDistribution() const;


    ///@brief Reseed object with the target seed.
    ///@param seed - The seed that the random number generator will
    ///be initialized. If seed is kRandomSeed it will be
    ///selected from the system std::time(nullptr).
    ///@see getSeed(), isUsingRandomSeed().
    void reseed(int seed = kRandomSeed);

    ///@brief Gets the actual seed used.
    ///@returns The actual seed used in this object - If Random was created
    ///using kRandomSeed it will the chosen seed, otherwise will return the
    ///argument used in the CTOR.
    int getSeed() const;

    ///@brief Checks if CTOR was initialized with kRandomSeed.
    ///@returns True if kRandomSeed was used, False otherwise.
    bool isUsingRandomSeed() const;


    // Private Methods //
private:
    inline void resetRange(int min, int max);


    // iVars //
private:
    //Housekeeping.
    int  m_seed;
    bool m_isUsingRandomSeed;

    //Random.
    NumberGeneratorType     m_rnd;
    IntegerDistributionType m_dist;
    IntegerDistributionType m_randomDist;
};


NS_CORERANDOM_END
#endif // defined(__CoreRandom_include_Random_h__) //
