// SkynetHKAerial.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int main() // main function
{
	srand(static_cast<unsigned int>(time(0))); //seed random number generator

	const int ROWS = 8; // Number of units wide the grid is, this will never change, so const int is declared
	const int COLUMNS = 8; // Number of units tall the grid is, this will never change, so const int is declared
	const int targetPos = rand() % 64 + 1; // Position the target is at on the grid, this will never change, so const int is declared
	int dronePos = rand() % 64 + 1; // Position the drone is at on the grid, this will change, so int is declared
	int numSearched = 0; // This is how many tries it took the AI to locate the target
	vector <int> searched; // This is a vector, operates as a list whos size can be changed, it will hold all the squares the computer searched through
	int grid[ROWS][COLUMNS] = { {1,2,3,4,5,6,7,8},
								{9,10,11,12,13,14,15,16},
								{17,18,19,20,21,22,23,24},
								{25,26,27,28,29,30,31,32},
								{33,34,35,36,37,38,39,40},
								{41,42,43,44,45,46,47,48},
								{49,50,51,52,53,54,55,56},
								{57,58,59,60,61,62,63,64} }; // This is a 2D array, it will serve as our 8x8 map, the numbers are stored as ints to use as comparison values later in the program.

	// This displays the default grid map
	for (int row = 0; row < ROWS; row++) // looks through every row
	{
		for (int col = 0; col < COLUMNS; col++) // looks through every column
		{
			cout << " -"; // print a " -" in the grid at position row, column, like a graph.
		}
		cout << endl; // We use an endline here, so we make the picture properly form a grid
	}
	Sleep(1000); // Sleep will temporarily pause the program for miliseconds, in this case 1000 is used, so the user can look at the default map momentarily
	system("cls"); // "cls" is very important in this program, it serves to format the screen, and allow the for loops to redraw the grid, like rendering in old video games
	
	searched.push_back(dronePos); // We add our first drone position initialized above to the vector names searched. We must do this here, or find has no elements to search through, and will give errors.

	// This is the main game loop
	while (dronePos != targetPos) // if dronePos doesn't equal targetPos go into this loop!
	{
		if (*(find(searched.begin(), searched.end() - 1, dronePos)) != dronePos) // if we cannot find the current drone position in the vector we go here.
																				 // the * (astrisk) here pulls the int value from the pointer, so we can use it for comparison
																				 // find returns a vector pointer, so it is important to use the astrisk
																				 // find looks through a given vector to see if it is currently holding the item its looking for, keep reading
																				 // searched.begin() searched is our vector name, begin tells find where to start, begin in this case is blank, so we start from the first iterator
																				 // searched.end() -1 searched is our vector name again, end tells find where to stop, but because end is not a value stored in the vector it returns an error when a null type is searched. To fix this we subtract 1 to tell end that it is actually ending on the last element of the vector.
																				 // dronePos is what find is trying to locate
																				 // != means does not equal
																				 // and lastly we have drone position being compared
																				 // simplified this statement means, look inside the searched vector, if we cannot find a value in the vector equal to the value of dronePos, we will go into this if statement. We need this, so we don't check numbers that we have already checked.
		{
			searched.push_back(dronePos); // This adds the drone position to the vector named searched
			// This loop redraws the grid, and puts X's where it needs to.
			for (int row = 0; row < ROWS; ++row) // look through all the columns
			{
				for (int col = 0; col < COLUMNS; ++col) // look through all the columns
				{
					if (dronePos == grid[row][col]) // If dronePos equals the value stored in a 2D array at our current coordinates
					{
						cout << " X"; // Put an X on the map at the drones current position
					}
					else if (*(find(searched.begin(), searched.end() - 1, grid[row][col])) == grid[row][col]) // if the above isn't true, we will look into our vector named searched to see if we have searched this square before, and if we have
					{
						cout << " X"; // Put an X there
					}
					else // if neither of the above is true
					{
						cout << " -"; // Put a dash " -", this is for formatting our grid, so we can see where we have searched and where we have not
					}
				}
				cout << endl; // This will return to a new line every time we finish reading through one of our rows of 8 characters
			}
			cout << "Blocks Searched: "; // simply let the user know that the numbers following this have already been searched
			for (int element = 0; element != searched.size(); ++element) // look through every element of our vector
			{
				cout << searched[element] << " "; // Display every number we have searched through
			}
			cout << endl << endl << "Drone Position: " << dronePos << endl; // print the current drone position
			cout << "Target Position " << targetPos << endl; // print the current target position, we include this, so the user knows what the computer is searching for
			numSearched++; // add 1 to the number of blocks we have searched, we add this down here outside of the loops, because we only want to add 1 when we search a new block
			Sleep(500); // pause the program, so the user can enjoy watching the drone search
			system("cls"); // Clear the console screen, so we can redraw the grid
		}
		dronePos = rand() % 64 + 1; // This will force the drone to select a new position, so we can evaluate the while loop again, instead of getting stuck in the loop infinitely.

	}


	// This is the 3rd time you've seen this in the program. It will draw the final map, with the location of the target marked as an O.

	for (int row = 0; row < ROWS; ++row) 
	{
		for (int col = 0; col < COLUMNS; ++col) 
		{
			if (targetPos == grid[row][col]) // We make this our if marker, because if we have left the while loop, we know that our drone is currently on target location, and we want to make an O instead of an X
			{
				cout << " O"; // Put an O on the map at the targets location
			}
			else if (*(find(searched.begin(), searched.end() - 1, grid[row][col])) == grid[row][col])
			{
				cout << " X"; 
			}
			else 
			{
				cout << " -"; 
			}
		}
		cout << endl; 
	}

	cout << "\n\nTarget sighted at " << dronePos << ". \nEngaging target.\nTarget eliminated."<< endl; // simple cout that prints the drones position when he found the target
	cout << "\nAction Report: " << numSearched +1 << " blocks were searched before target was located, and destroyed." << endl; // simple cout that prints the number of blocks we searched before target was located +1 for the default initialization
	system("pause"); // pause the system, so the user can see the action report
	return 0; // return 0, because we don't need to do anything with the return of this program
}