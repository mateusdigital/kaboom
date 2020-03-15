# CoreClock

**Made with <3 by [Amazing Cow](http://www.amazingcow.com).**



<!-- ####################################################################### -->
<!-- ####################################################################### -->

## Websites:

* [CoreClock Website](http://opensource.amazingcow.com/gamecore/coreclock/)
* [Game Core Website](http://opensource.amazingcow.com/gamecore/) - 
The Amazing Cow's Game Cores site.



<!-- ####################################################################### -->
<!-- ####################################################################### -->

## Description:

```CoreClock``` is a small library intended to easy the time tracking in games,
but it general enough to be used in a myriad of situations.  
It can be used to _fire events_ after some time, giving a very flexible way 
to handle animations, callbacks and other stuff. 


### Motivation:

In some games we need to perform some operation repeatedly, or after some time.    
So instead of messing with _ivars_ to keep track of time and all other _"low-level"_
stuff we decide to create the ```CoreClock``` class to keep it very encapsulated.


<br>
As usual, you are **very welcomed** to **share** and **hack** it.




<!-- ####################################################################### -->
<!-- ####################################################################### -->

## Examples:

Let's imagine a scenario that we want to trigger some operation 3 times with 
1 second between them. This will let us appreciate how CoreClock will ease our lives.

#### One possible implementation could be:

```c++
///////////////////////////
//In SomeClass.h         //
///////////////////////////
float m_timeSinceLastTick;
float m_timeToTick; 
float m_repeatTickCount;


///////////////////////////
//In SomeClass.cpp       //
///////////////////////////
void SomeClass::initClock()
{
    m_timeSinceLastTick = 0;
    m_timeToTick        = 1000; //Milliseconds...
    m_repeatTickCount   = 3;    //We gonna decrement it...
}

void SomeClass::update(float dt)
{
    //This is straightforward, but we don't like to have to 
    //do this every time that we need a timer of some sort.
    m_timeSinceLastTick += dt;
    if(m_repeatTickCount > 0 && m_timeSinceLastTick >= m_timeToTick)
    {
        m_timeSinceLastUpdate -= m_timeToTick;
        
        this->doSomethingCool(); //Trigger the tick action.

        --m_repeatTickCount;
    }
}
```

We find this very, very cumbersome, not clear, ugly...    

#### With CoreClock:

```c++
/////////////////////////
//In SomeClass.h       //
/////////////////////////
CoreClock::Clock m_clock;
...

///////////////////////////
//In SomeClass.cpp       //
///////////////////////////
void SomeClass::initClock()
{
    m_clock.setInterval(1000); //Ms, but can be anything that you like.
    m_clock.setRepeatCount(3);
    
    //This can be a lambda, a Functor etc...
    m_clock.setCallback(std::bind(&SomeClass::doSomethingCool,this));

    m_clock.start();
}

void SomeClass::update(float dt)
{
    //Clock will ignore updates after 3 ticks...
    m_clock.update(dt);
}

```

Much more easier hun???




<!-- ####################################################################### -->
<!-- ####################################################################### -->

## Documentation:

We strive to make our source code fully documented.   
While there are a myriad of comments, one might find useful take a look at:

* [Project Website](http://opensource.amazingcow.com/gamecore/coreclock/).
* [Doxygen Docs](http://opensource.amazingcow.com/gamecore/coreclock/doxygen/).
* [A list of blog posts about the project](http://opensource.amazingcow.com/gamecore/coreclock/posts/).

Anyway if you didn't understand something let us know sending a mail to  
[help_opensource@amazingcow.com]() with the subject filled with the
name of this repo.



<!-- ####################################################################### -->
<!-- ####################################################################### -->

## Dependencies:

There is no dependency for ```CoreClock```.



<!-- ####################################################################### -->
<!-- ####################################################################### -->

## License:

This software is released under GPLv3.



<!-- ####################################################################### -->
<!-- ####################################################################### -->

## TODO:

Check the TODO file for general things.

This projects uses the COWTODO tags.   
So install [cowtodo](http://www.github.com/AmazingCow-Tools/COWTODO) and run:

``` bash
$ cd path/to/the/project
$ cowtodo 
```

That's gonna give you all things to do :D.



<!-- ####################################################################### -->
<!-- ####################################################################### -->

## Others:

Check our repos and take a look at our 
[open source site](http://opensource.amazingcow.com).
