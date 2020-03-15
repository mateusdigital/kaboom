# CoreRandom

**Made with <3 by [Amazing Cow](http://www.amazingcow.com).**



<!-- ####################################################################### -->
<!-- ####################################################################### -->

## Websites:

* [CoreRandom Website](http://opensource.amazingcow.com/gamecore/corerandom/)
* [Game Core Website](http://opensource.amazingcow.com/gamecore/) - 
The Amazing Cow's Game Cores site.



<!-- ####################################################################### -->
<!-- ####################################################################### -->

## Description:

```CoreRandom``` is a easy to use random number generator inspired in C# 
System.Random class.


### Motivation:

Often in games we need a random generator. While this can be easily used using 
the c++11 ```<random>``` facilities, we think that must have a cleaner way.

This core is basically a glue between the ```std::mt19937``` generator and 
```std::uniform_int_distribution``` distribution - Nothing fancy, but yet 
very nice to use.

We tried to add an interface for ```CoreRandom::Random``` much alike of C# 
```System.Random``` - So is very easy to use the same ```CoreRandom::Random``` 
object to generate random values from arbitrary ranges each time :D

<br>

As usual, you are **very welcomed** to **share** and **hack** it.



<!-- ####################################################################### -->
<!-- ####################################################################### -->

## Examples:

```CoreRandom``` is very easy to use.

```c++
CoreRandom::Random random;

random.next(10);       //0 to 10    - Inclusive.
random.next(100, 200); //100 to 200 - Inclusive;

//Play nice with other std algorithms...
std::shuffle(container.begin(),
             container.end(),
             random.getNumberGenerator());
```


### Notes:

The ```CoreRandom::Random::next()``` and it's overloads will reset the 
underlying ```std::uniform_int_distribution::param_type``` value if the them are
called with different ranges from the previous call.

For example:

```c++
CoreRandom::Random r;

r.next();         //No modify - We start with range of [0, std::limits<int>::max()];
r.next(10);       //Modify    - Now the range will be [0, 10];
r.next(10);       //No modify - Same range [0, 10];
r.next();         //Modify    - Now range is [0, std::limits<int>max()];
r.next(100, 200); //Modify    - Now the range will be [100, 200];
r.next(100, 200); //No modify - Same range [100, 200];

//And so on...
```

We don't expect that this could be a performance bottleneck - After all the 
```std::uniform_int_distribution``` and ```std::uniform_int_distribution::param_type```
are very lightweight objects.   
But this way could not be the optimal way of achieve the desired results if 
we are changing ranges **very**, **very** often. Instead one could prefer create
manually a generator and a myriad of distributions and keep them separated from
each other. 

For example:

```c++ 
//Doing this will perform better...
std::mt19937 gen(time(nullptr));
std::uniform_int_distribution<int> a(1, 5);
std::uniform_int_distribution<int> b(10, 15);
std::uniform_int_distribution<int> c(20, 25);

for(;;)
{
    cout << a(gen) << endl;
    cout << b(gen) << endl;
    cout << c(gen) << endl;
}

//Compared of doing this...
Core::Random r;
for(;;)
{
    cout << r.next( 1,  5) << endl;
    cout << r.next(10, 15) << endl;
    cout << r.next(20, 25) << endl;
}
```

Notice that the example above is the **worst-case** possible for 
```CoreRandom::Random``` since each call of next(x, y) it will reset the 
underlying ```std::uniform_int_distribution::param_type```.

We **DID NOT** any type of measurement to check how bad is this type of use - 
So use the ```CoreRandom::Random``` in this way by your own risk.



<!-- ####################################################################### -->
<!-- ####################################################################### -->

## Documentation:

We strive to make our source code fully documented.   
While there are a myriad of comments, one might find useful take a look at:

* [Project Website](http://opensource.amazingcow.com/gamecore/corerandom/).
* [Doxygen Docs](http://opensource.amazingcow.com/gamecore/corerandom/doxygen/).
* [A list of blog posts about the project](http://opensource.amazingcow.com/gamecore/corerandom/posts/).

Anyway if you didn't understand something let us know sending a mail to  
[help_opensource@amazingcow.com]() with the subject filled with the
name of this repo.



<!-- ####################################################################### -->
<!-- ####################################################################### -->

## Dependencies:

There is no dependency for ```CoreRandom```.



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
