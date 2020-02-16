# Prototype of game Breakout

Breakout is a prototype game project based on Windows 10 OS. The game’s purpose is to hit and break the bricks on the upper side of the game scene by using the ball. The player’s role is to control the paddle on the bottom of the game window by moving it to left or right and catching the ball flying towards the bottom of the window. The ball will be reflected and hit the bricks if the player successfully catches the ball. The player wins the game if he/she breaks all the bricks. The game ends if the ball hits the bottom of the window three times. 
The game was built using SDL 2 library and C++. IDE used for this game is Dev-C++. No extra libraries or borrowed code was included. 
The code structure is simple for now as all objects appear in the game have their own struct (ball, paddle, bricks, player life indicator, background, renderer and game window). 


## Installation

To run and play the game simply double click the ‘Breakout.exe’ included in the project folder. For developers use Dev-C++ to edit and rebuild the project (Using Breakout.dev file).



## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## Roadmap
The project is currently on its version 2.0. There are several plans under construction. Future releases and features are listed below:
Version 2.1: Rebuild the app using better code structure including using more classes to group functions and avoid problems brought by global declared structs. A restart game feature will be added. 
Version 2.2: Completing the game by adding start screen, levels and sound effect. 
Version 3: Introducing AR to Breakout. The player may interact with his/her hand. The platform will be moved to iOS. 


## License
[MIT](https://choosealicense.com/licenses/mit/)
