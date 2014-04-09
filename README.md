battleship
==========

Battleship game (Zeeslag)

	   // Created by Jonathan van der Steege (March 2014)
	   // jonakeys@hotmail.com
	   // Written in C++

// GOAL 
Two players battle to rule the open sea. The goal is to destroy all of the enemy's ships.
The first player who does so, wins the game. A ship is destroyed when all it's coordinates are revealed.

// START
The game starts with each player placing their ships on the playing field. Ships can only be placed 
horizontally or vertically and aren't allowed to be adjacent to each other.

Each player has 10 ships:
1 Battleship  	  (4 4 4 4)
2 Cruisers    	  (3 3 3) (3 3 3)
3 Torpedo Boats	  (2 2) (2 2) (2 2)
4 Submarines	  (1) (1) (1) (1)

// BATTLES
In turn, each player fires a shot. When it hits, the number of the ship is revealed. When the shots misses, 
an 'm' is displayed on the field. There are 20 hits left. When the counter reaches 0, you have won.

// OPTIONS
In the main menu there's an option to play versus the computer (AI). The AI finds locations where ships
are at and searches around them. It even checks smart if there are already 2 locations aligned and acts
accordingly.
When the game is won and the program quits, the results are written to a file named 'statsFile.txt'
in the same directory as the game is run.

// ENDING NOTES
Have fun playing the game! I would like to hear from you if you compiled and played the game and what you
think of it. Also I would like to improve my programming skills, so feel free to comment about that too!

-- Jonathan