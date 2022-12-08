Built Sept 2020

# My Solution to Ableton's Task 1: Modular Madness

www.eloibarti.com  
www.github.com/ebarti  
www.soundcloud.com/tremoleda

## On the selected Unit Test Framework
Although I have mostly worked with custom test Frameworks in my professional experience,
I also have some experience with open-source test frameworks such as [Google Test][GTest].

However I have decided to use [Catch][catch] as the test framework of choice for this implementation, as
I have observed Ableton's code magicians have already used it within [Link][link]

## Build Instructions
Requirements: [CMake][cmake]  3.16+
Note: this version does not accept running in interactive command line mode! Thus, either a file or a string of commands must be provided.  
On the root source folder of this project .../AbletonTask1 , run:

```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

The output binaries for the Command Line application, as well as the binaries for the unit tests
will be placed in a `bin` subdirectory of the CMake binary directory.

## Running Unit Tests
On the build folder of this task, .../AbletonTask1/build , run:  
```
$ cd bin
$ ./AbletonTask1_Tests
```

To get a list of the tests (Catch2 enabled), use:
```
$ ./AbletonTask1_Tests -l
```

For more options:
```
$ ./AbletonTask1_Tests -?
```

## Usage
The binary AbletonTask1, located in AbletonTask1/build/ should be run as:  
`./AbletonTask1 [commands]`  
Or alternatively, you can pipe input as:  
`./AbletonTask1 < path_to_file_defining_input`
## On my solution
_First and foremost, my apologies if some (or all) of my assumptions do not match at all
how a "real" audio application works._

On the definition of this Modular Madness exercise, it reads:

> _In a “real” audio application, modules have to be processed in the order of their
>dependencies. [...] please note that this makes this task considerably harder._

Well then I must be a masochist, as **I have choosen the more realistic approach**.
I see this problem of connected modules as a **directed cyclic graph** (more on that later).

### Assumptions
#### First and last modules
As directed cyclic graphs do not have a defined start or end point, I will assume that:
1. The first module created is the first module in the graph. That is, it will be the first module to receive the raw tokens from the input stream.
2. The last module created is the last module in the graph. That is, the output will read whatever this module outfeeds.
3. A module does not necessarily need to be connected. Note, however, that if the first or the last modules are left unconnected **there will be no output.**
4. A module can only feed to another module once.

Now, for some examples. Consider the following command succession:

```
module beta delay
module epsilon reverse
module gamma echo
connect beta gamma
process hello world
```

The first module is beta, and the last module is gamma. Module epsilon is left unused, thus is not part of the processing solution.
```
           +------+    +---------+    +-------+
           |      |    | epsilon |    |       |
input +--->+ beta |    +---------+    | gamma +---> output
           |      +------------------>+       |
           +------+                   +-------+
```
The output string returned by the program will be:  
```
hellohello hellohello worldworld
```

Another example:
```
module epsilon reverse
module beta delay
module gamma echo
connect beta gamma
process hello world
```

Equals
```
                          +------+    +-------+
           +---------+    |      |    |       |
input +--->+ epsilon |    | beta +--->+ gamma +---> output
           +---------+    |      |    |       |
                          +------+    +-------+
```
Which does not output anything.

This is an example where the condition of a module feeding another module only once is applied:
```
module beta delay
module gamma echo
connect beta gamma
connect gamma beta
connect beta gamma
process hello world
```

Becomes:
```
           +------+    +-------+
           |      +--->+       |
input +--->+ beta |    | gamma +---> output
           |      +<---+       |
           +------+    +-------+
```

And its output is LIMITED by
>_The number of output strings must be limited to sixteen times the number of input strings in the corresponding process line_

### Implementation
As you will quickly see, the implementation of this task is nowhere near optimized. I have used
a self contained approach to treat modules and their connectivity, checking whether a new connection creates
a reference to avoid infinite looping when visiting each module.  
This could have been solved with a more 'mathematical' approach, although I must say I have a weakness for visitors :)

[GTest]: https://github.com/google/googletest
[catch]: https://github.com/philsquared/Catch
[cmake]: https://www.cmake.org
[link]: https://github.com/Ableton/link
