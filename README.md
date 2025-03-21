
# Donkey Kong in Console


![Menu](https://github.com/1mache/DonkeyKongCPP/blob/main/screenshots/menu.png)

This project was done for our "Object Oriented Programming in C++" course in college. It is a copy of a well known arcade game that runs in your console :)


## Authors

- [@1mache](https://www.github.com/1mache)
- [@BenLiberman](https://github.com/Ben-GitCode)
## Acknowledgements

 - [Premake5](https://github.com/premake/premake-core)
We put the premake exe file for windows in premake/ for convenience. [Here](https://premake.github.io/download) you can download premake for other OS.

## Rules and gameplay
- The goal of the game is to reach the princess while dodging various enemies.
- You can also kill the enemies with a hammer after you pick it up.
- Controls can be checked in the main menu. **Make sure you have English selected when playing :)**
- You have 3 lives, and you earn score for killing enemies and finishing levels quickly.
- Barrels are spawned by Donkey Kong and decide what direction to roll in based on floor (`>` or `<`) or continue their previous direction if the floor is neutral (`=`)
- Regular ghosts move on platforms, they can't fall from platforms so if they reach the end they change direction. They can also change the direction randomly.
- Climbing ghosts follow you around, can climb ladders and you can't jump over them. The only way to escape them is killing them.

#### Here are the "sprites" used for game entities/objects:
| Sprite | Description                          |
| :-------- | :-------------------------------- |
| `@`       | Mario  |
| `&`       | Donkey Kong  |
| `$`       | Pauline (princess)  |
| `O`       | Barrel |
| `x`       | Ghost  |
| `%`       | Climbing Ghost (follows you) |
| `H`       | Ladder (you can climb them) |
| `p`       | Hammer |

**Hold on to your 3 lives or else...**
![Menu](https://github.com/1mache/DonkeyKongCPP/blob/main/screenshots/gameOver.png)

## Building

Build the project by running:
```bash
  premake/premake5.exe vs2022
```
(if you're using VisualStudio2022)\
Or by executing build.bat (on Windows).\
This will create VisualStudio2022 project files inside DonkeyKong/ folder.

This was tested on Windows, but in theory you should be able to build the project files for your specified editor if premake supports it.

## Manual Configuration

The game is intended to run in an **80x25** console which may not be the default size of your console. If your console window is bigger, you can still play just fine, but if its smaller the game is unplayable. You can change the window dimensions in the console settings.

If the game is too fast/slow for you you can change the\
`GAME_REFRESH_RATE`\
variable in GameOptions.h .  
