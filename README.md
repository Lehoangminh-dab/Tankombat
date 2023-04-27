# TANKOMBAT
A non-commercial game made using C++ and the SDL2 library.
Homework of UET's 2023 Advanced Programming Class (INT 2215).

# Introduction
* Game Type: 4 player local offline multiplayer shooter.

# The Narrative 
You are a tank who really likes to spin around, for some reason. During your adventures on the brutal battlefields of war, you suddenly encounter 3 other tanks who also likes spinning around, exactly like you. After extremely little consideration, all 4 tanks decide there can only be one tank-that-spins to rule them all. And now, all 4 tanks must try to eliminate each other until there is only one tank left standing. En Garde!

# Play Guide
Each player has exactly one button to control their tanks. When a  button is pressed, the corresponding tank stops spinning, then fires a bullet in the direction of its cannon, then moves forward until the button is lifted.
## The Objective
Shoot, move, dodge each other's bullets until there is only one player standing!

## Tank Controls
* BLUE Tank: Press X to shoot and move forward
* BROWN Tank: Press RIGHT SHIFT to shoot and move forward
* GRAY Tank: Press LEFT TAB to shoot and move forward
* GREEN Tank: Press BACKSPACE to shoot and move forward

## Gameplay controls
* Press the ESC key to pause the game during gameplay.


# Game Demo

# Function
The game has the following features:
## The Main Menu
* Play Button: Initializes gameplay.
* Controls Button: Where you can learn how to control your tank.
* Exit: Closes the game.
## The Gameplay
When you're in a match, you could explore the following features:
* Press (Your Tank's Button) to stop your tank from rotating, send a bullet forward and get one step closer to victory.
* Release (Your Tank's Button) to stop your tank from moving, start spinning once again and give yourself an opportunity to reorient your tank.
### The Pause Menu
When you press the ESC key to pause the game, you will see 3 buttons:
* Resume Button: Stop the game from pausing, and resume the gameplay
* Restart Button: Stop the game from pausing, and start a new match from the beginning.
* Quit Button: Stop the game and quit to the Main Menu.
### The Winning Menu
When there's only one player left surviving, a winning menu will appear, announcing the winner and displaying 2 buttons:
* Restart Button: Start a new match from the beginning.
* Quit Button: Quit to Main Menu.
# Installation
Note: This game is only tested in Windows environment and is compiled using Visual Studio Community 2022
* Step 1: Download Visual Studio Community 2022 from [Microsoft page](https://visualstudio.microsoft.com/vs/community/).
* Step 2: Install the Visual C++ compiler and then put the directory address in System Path. (Or download the Visual C++ package that is displayed as an option when you first launch Visual Studio)
* Step 3: Download the source code from this repository
* Step 4: Install the SDL2 libraries (including SDL2, SDL2_image, SDL2_ttf, SDL2_mixer)
* Copy all the headers of SDL2 (for example: SDL.h) into the sdl folder (which should be created in include folder)
Copy all the libraries of SDL2 (cmake, pkgconfig, libSDL2) into the lib folder (which should be created in main directory)
Copy all the SDL dll files into the main directory
* Step 5: Press the shortcut "Ctrl + B" in Visual Studio.
* Step 6: After the game is compiled successfully, you will the an executable file named "main.exe" and you can open this file to play the game!
# Credits
* This project is made by Le Hoang Minh
* Game assets were taken from various sources, like:
  * Itch.io
  * opengameart.org
  * Etc...
# Licenses
This is a free and non-commercial piece of software. You are free to use it however you want.
