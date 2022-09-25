# CPP Game

Learning c++ while making a game with [SDL2](https://www.libsdl.org/download-2.0.php).

## The Game

The Game resembles the [Bastion Stairs Workshop Minigame](https://workshop.codes/62TWS) from Overwatch.
Press space to jump up and left control to switch directions (you start facing left). Instead of scores and restarting at 0 when failing, you have some sort of error bar, which tells you the amount of errors per layer you advanced.

## Project Structure

You need to add the SDL2 files (.dll, include and lib) yourself (maybe i will add them to a github release). 
```
mainFolder
- include
  - SDL2
- lib
- src
.gitgnore
Makefile
SDL2.dll
```
