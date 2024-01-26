/*
* Name: Rahel Siefe, 5007247591, Assignment #7
* Description: This sweepminer program builds a 2D grid where bombs
are placed randomly. Each square hold a number represeting its distance
from the nearest bomb. Squares with bombs should be marked accordingly;
* Input: Coordinates on the board, distance from a bomb, bomb count 
* Output: Prints a populated sweepmine baord according to where
the closest bomb is realtive ot each unit of the baord. 
*/

#include "sweepminer.h"
#include <iomanip>
#include <vector>

using namespace std;

// vv Uncomment next line to get helpful debug statements, but leave commented for final submission vv
// #define DEBUG
/* 
 allocateBoard: Dynamically allocates the 2D board array and populates 
 it with maxDist in each entry. 
 parameters: None.
 return value: None.
 */
void Sweepminer::allocateBoard()
{
	int maxDist = width + height + 1; // Maximum possible distance a space could be from bomb
	//Dynamically allocating the 2D board array
	board = new int *[height];
	//filling the board with maxDist to mark as uninitialized
	for (int i = 0; i < height; i++)
	{
		board[i] = new int[width];
		for (int j = 0; j < width; j++)
		{
			board[i][j] = maxDist;
		}
	}
}

/* 
 deallocateBoard: Deallocating the 2D board array.
 parameters: None.
 return value: None.
*/
void Sweepminer::deallocateBoard()
{
	for (int i = 0; i < height; i++)
		delete [] board[i];
		
	delete[] board;
}

/* 
 generateDistances: This function recursively marks the distances of all squares
 to the closest bomb.
 parameters: Position object pos, int distance 
 return value: None.
 */
void Sweepminer::generateDistances(Position pos, int distance)
{
	//checks if positions are within the bounds of the board 
	if (pos.x >= width || pos.x < 0 || pos.y >= height || pos.y < 0)
		return;

	// If the position on the board is already closer to another bomb (i.e.
	// the distance in the current spot is less than the distance param)
	// Then it does not need replaced
	if (distance >= getDistanceAtPosition(pos))
		return;

	// the distances are replaced and the adjacent squares
	// the distances generated 
	setDistanceAtPosition(pos, distance);
	generateDistances(pos.addPosition(-1, 0), distance + 1);
	generateDistances(pos.addPosition(0, 1), distance + 1);
	generateDistances(pos.addPosition(1, 0), distance + 1);
	generateDistances(pos.addPosition(0, -1), distance + 1);
	
}

//------------------------------------ FUNCTIONS FOR SKELETON ------------------------------------
/* Populates the board by randomly generating where the bombs go and then
calling the generateDistances function to fill in the distances */
void Sweepminer::populateBoard(const int &bomb_count)
{
	vector<Position> bombPositions;
	int i, j;
	Position *temp;
	bool duplicatePosition = false;

	for (i = 0; i < bomb_count; i++)
	{
		// Generate the next bomb position and make sure it's not a duplicate
		temp = new Position(rand() % width, rand() % height);
		while (duplicatePosition)
		{
			duplicatePosition = false;
			for (j = 0; j < (int)bombPositions.size(); j++)
			{
				if (bombPositions[j] == *temp)
				{
					duplicatePosition = true;
					break;
				}
			}
		}

		// Then, add the bomb and generate its distances
		generateDistances(*temp, 0); // Position is temp, distance to bomb is 0
		delete temp;

// Debug print info
#ifdef DEBUG
		cout << "Board after putting bomb " << i << " at (" << temp.x << ", " << temp.y << ")" << endl;
		printBoard();
#endif
	}
}

/* 
 printBoard: Prints all of the distances to flags to the terminal.
 parameters: None.
 return value: None.
*/
void Sweepminer::printBoard()
{
	int i, j;
	cout << setfill('-') << setw(3 * width + 3) << "" << setfill(' ') << endl; // Print top border
	for (i = 0; i < height; i++)
	{
		cout << "| "; // Print left border
		for (j = 0; j < width; j++)
		{
			if (board[i][j] == 0) // If this spot contains a bomb/flag, print its
				cout << " " << flag << " ";
			else // Else print the distance
				cout << setw(2) << right << board[i][j] << " ";
		}
		cout << "|" << endl; // Print right border
	}
	cout << setfill('-') << setw(3 * width + 3) << "" << setfill(' ') << endl; // Print bottom border
}
