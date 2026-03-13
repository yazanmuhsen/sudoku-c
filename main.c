#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void fill0(int a[9][9]) // Initialize the sudoku and prepare it to be filled
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			a[i][j] = 0;
		}
	}
}

void printGrid(int a[9][9]) // Printing the sudoku using a map style I designed
{	printf("\t 1  2  3\t 4  5  6\t 7  8  9");
	for (int i = 0; i < 9; i++) {
		if(i>0)
			printf(" %d",i);

		if (i % 3 != 0)
			printf("\n");
		if (i % 3 == 0) {
			printf("\n\t_________\t_________\t_________\n"); //  __
			// |#|
		}
		for (int j = 0; j < 9; j++) {
			if (j % 3 == 0)
				printf("\t");
			if (a[i][j] == 0)
				printf("|.|");  // The numbers that are required to be fill will be printed as |.|
			else
				printf("|%d|", a[i][j]);
		}
	}
	printf(" 9");
	printf("\n\t_________\t_________\t_________");
}

int checkValid(int a[9][9], int num, int row, int col) // Check the if the number is valid in a position.

{
	// Check row and column.
	for(int i = 0; i < 9; i++)
	{
		if(i != col && a[row][i] == num)
			return 0;
		if(i != row && a[i][col] == num)
			return 0;
	}

	// Check 1st 3x3 block
	if(row < 3 && col < 3)
	{
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(i == row && j == col) continue; // Check all rows and columns except the one's the number is in.
				if(a[i][j] == num) return 0;
			}
		}
	}
	// Check 2nd 3x3 block

	if(row < 3 && col >= 3 && col < 6)
	{
		for(int i = 0; i < 3; i++)
		{
			for(int j = 3; j < 6; j++)
			{
				if(i == row && j == col) continue;
				if(a[i][j] == num) return 0;
			}
		}
	}
	// Check 3rd 3x3 block

	if(row < 3 && col >= 6 && col < 9)
	{
		for(int i = 0; i < 3; i++)
		{
			for(int j = 6; j < 9; j++)
			{
				if(i == row && j == col) continue;
				if(a[i][j] == num) return 0;
			}
		}
	}
	// Check 4th 3x3 block

	if(row >= 3 && row < 6 && col < 3)
	{
		for(int i = 3; i < 6; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(i == row && j == col) continue;
				if(a[i][j] == num) return 0;
			}
		}
	}
	// Check 5th 3x3 block

	if(row >= 3 && row < 6 && col >= 3 && col < 6)
	{
		for(int i = 3; i < 6; i++)
		{
			for(int j = 3; j < 6; j++)
			{
				if(i == row && j == col) continue;
				if(a[i][j] == num) return 0;
			}
		}
	}
	// Check 6th 3x3 block

	if(row >= 3 && row < 6 && col >= 6 && col < 9)
	{
		for(int i = 3; i < 6; i++)
		{
			for(int j = 6; j < 9; j++)
			{
				if(i == row && j == col) continue;
				if(a[i][j] == num) return 0;
			}
		}
	}
	// Check 7th 3x3 block

	if(row >= 6 && row < 9 && col < 3)
	{
		for(int i = 6; i < 9; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(i == row && j == col) continue;
				if(a[i][j] == num) return 0;
			}
		}
	}
	// Check 8th 3x3 block

	if(row >= 6 && row < 9 && col >= 3 && col < 6)
	{
		for(int i = 6; i < 9; i++)
		{
			for(int j = 3; j < 6; j++)
			{
				if(i == row && j == col) continue;
				if(a[i][j] == num) return 0;
			}
		}
	}
	// Check the last 3x3 block

	if(row >= 6 && row < 9 && col >= 6 && col < 9)
	{
		for(int i = 6; i < 9; i++)
		{
			for(int j = 6; j < 9; j++)
			{
				if(i == row && j == col) continue;
				if(a[i][j] == num) return 0;
			}
		}
	}

	return 1; // Availble spot
}


int checkWin(int a[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (a[i][j] == 0 || checkValid(a, a[i][j], i, j) == 0)
				return 0;
		}
	}
	return 1;
}

void genSudoku(int a[9][9]) // The most difficult function made in this code. It generates a true sudoku map.
{
	int valid, num, count;
	srand(time(NULL));

	while (1) {
		fill0(a); // The array is initialized
		int failed = 0; // A boolean to test if the random numbers filled work or not.

		for (int i = 0; i < 9; i++) // nested loop to fill the sudoku
		{
			for (int j = 0; j < 9; j++) {
				count = 0; // The code will have 20 tries to fill each number if it fails to fill then the code will initialize and try again.
				valid = 0; // A bolean that tests if the random number filled works or not.

				while (count < 20 && valid == 0) {
					num = rand() % 9 + 1; // Random number generated.
					if (checkValid(a, num, i, j) == 1) // Calls the function to test if the number applies to the sudoku rules.
					{
						valid = 1; // If the number is positioned correctly its assigned.
						a[i][j] = num;
					}
					count++; // Counts to 20 tries.
				}

				if (valid == 0) // The loop tried 20 times to give a suitable number and failed, it will initialize the array and try again.
				{
					failed = 1;
					break; //Breaks from the (j loop).
				}
			}
			if (failed == 1) //Breaks from the (i loop).
				break;
		}

		if (failed == 1) // "Skips" the first while loop and starts from scratch
			continue;

		if (checkWin(a) == 1) // After many tries we will eventually get a random, but correct sudoku map and will stop the loop.
			//The function's work is finished.
			break;
	}
}


void genPuzzle(int a[9][9]) // A copy of the filled sudoku map that will remove random numbers from the map.
{
	srand(time(NULL));
	int x, y, count1, count;
	count = 0;
	count1 = rand() % 6 + 51; // It will delete 50-35 hints which is enough to make the game challenging.
	while (count < count1) {
		x = rand() % 9; // Random positions.
		y = rand() % 9;
		a[x][y] = 0;
		count++; // Will keep removing hints until only 26-30 is availble.
	}

	printGrid(a); // Prints the puzzle without the hints.
}

int main() {

	int sudoku[9][9];
	int puzzle[9][9] = {0};


	genSudoku(sudoku);


	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			puzzle[i][j] = sudoku[i][j]; // Copies the sudoku solution to the puzzle in order to print the puzzle without hints.
		}
	}


	genPuzzle(puzzle); // The function that deletes the hints and prints the puzzle.

	printf("\nThis is the Sudoku map! Let's see how you can solve it!\n");

	while (1) // The user has unlimited tries.
	{
		int row, col, num;
		printf("\nEnter the row (1-9), column (1-9), and number (1-9): ");
		scanf("%d %d %d", &row, &col, &num);
		row--;
		col--;

		if (row < 0 || row > 8 || col < 0 || col > 8 || num < 1 || num > 9) {
			printf("Invalid input! Please enter values within range.\n");
			continue;
		}

		if (puzzle[row][col] != 0) // The user shouldn't try to change a number already stated
		{
			printf("Cannot change original numbers!\n");
			continue;
		}

		if (num != sudoku[row][col]) // Checks the number with the solution
		{
			printf("Invalid move! \n");
			continue;
		}

		puzzle[row][col] = num; // The number is correct!
		printGrid(puzzle); // Prints the puzzle

		if (checkWin(puzzle) == 1) // Keeps checking if the user finished the sudoku correctly
		{
			printf("\nCongratulations! You solved the Sudoku!\n");
			break;
		}
		printf("\nWould you like a hint? Enter (1) for yes!\n");
		int hint=1;
		scanf("%d",&hint);
		if(hint) {
			for(int i=0; i<9; i++) {
				for(int j=0; j<9; j++) {
					if(puzzle[i][j]==0)
					{
						for(int k=1; k<=9; k++)
						{
							if(sudoku[i][j]==k) {
								printf("\nHint: Cell at Row %d, Column %d is %d\n", i+1, j+1, k);
								hint=0;
								break;
							}

						}
						if (!hint)
							break;
					}
					if (!hint)
						break;
				}
				if (!hint)
					break;
			}
		}


	}
}
