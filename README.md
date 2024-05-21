# Battleships

A simple game of battleships made using C++ and runs in a console window

This project was complete in my first year of a software engineering degree and was the second project I ever created using C++

### Introduction
Battleships is a strategy guessing game where you and the computer attempt
to destroy each others Battleships.

### Controls
The game begins with you placing your ships within the boundaries of the
10x10 game board.
Each ship has a designated size, can be placed either horizontally
or vertically, and cannot overlap one another.
When placing the ships, you specify a grid location beginning with a letter,
followed by a number (for example, 'A1'). 
The specified grid location refers to the left-most position of the ship
if placing horizontally, or the top-most position if placing vertically,
with the remaining grids being filled in their respective directions
(assuming there is enough space on the board).
If necessary, ships can be placed automatically for your ease.

Below is a list of your ship types along with their size.

Name			Size
Aircraft Carrier   	 5
Battleship         	 4
Destroyer          	 3
Submarine	   	 3
Patrol Boat	   	 2

Once placed on the game board, they are shown with a letter designation
based on the first letter of the ship name, for example, your Battleship
will be shown on the game board with a 'B'.

Once all ships have been placed, you and the computer will take turns guessing
grid locations in an attempt to destroy each others ships. Again, when choosing
a location to attack, specify a grid location beginning with a letter,
followed by a number.

If you manage to hit all positions of the enemy ship, you will be notified
which ship you have destroyed.

To win, you must destroy all of the computers ships before it destroys yours.

### Debug Mode
Also included with this project is a debug mode.

Debug mode can be accessed from the main menu. When selected, press 'Y' to 
turn debug mode on (or off), at which point you will be promted to return 
to the main menu to start your game.

Debug mode will show the AI game boards, including where the AI ships have
been automatically placed.
