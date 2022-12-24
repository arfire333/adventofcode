# About, how to build, how to run
A quick visualization of Day 23.  The visualization was the
focus more than code quality.  If you don't find code smells
while looking at the code, look harder.  I'm sure they are
there. :)

## Building
This is built using cmake from the top level directory of the repository.  CMake will download and build Raylib which is the 
main dependency.  Slightly more specific instructions are in 
the top level readme.

## Running
Simply run the executable and pass it the filename of the data.
Note that the path to the elf is hardcoded and relative to
the executable.  Specifically `resources/elf.png`.  Running
the debug test should handle everything for you using my
data.


