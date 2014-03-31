battleship
==========

Battleship game

	   // Created by Jonathan van der Steege (March 2014)
	   // jonakeys@hotmail.com
	   // Written in C++

-- GOAL --
Two players battle to rule the open sea. The goal is to destroy all of the enemy's ships.
The first one who does so, wins the game. A ship is destroyed when all coordinates of it are revealed.

-- START --
The game starts with each player getting to place their ships onto the playing field.
Each player has 10 ships:
1 Battleship  	  (4 4 4 4)
2 Cruisers    	  (3 3 3) (3 3 3)
3 Torpedo Boats	  (2 2) (2 2) (2 2)
4 Submarines	  (1) (1) (1) (1)

-- BATTLE --
In turn, each players gets to fire a shot. When it hits, the number of the ship is revealed.
When it misses, a 'M' is displayed on the field.