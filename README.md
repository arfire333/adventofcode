# Advent of Code
2021 - Not actually done in 2021
2022 - In progress...

## Dependencies

- jsoncpp 1.9.5-1 - Only for statviewer
- raylib - Only for the bonus round
- cmake - Only for the bonus round

## Building
### Regular
The regular puzzles are setup to be built in VSCode simply by pressing F5.

### Bonus Rounds
The puzzles animated with Raylib are built using cmake.  The following should
work for those.

```
mkdir build
cd build
cmake ..
cmake --build .
```

To execute the bonus round, it likely will have a default value so you can 
just run the program.  The more interesting ones should be passed the data 
file.  As of the time of this writing.  Only 2022/day_14 has a bonus.



