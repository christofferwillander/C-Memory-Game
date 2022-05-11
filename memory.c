/* 
 * Programmer: Christoffer Willander	Date completed: December 2nd, 2017
 * Instructor: Carina Nilsson			Class: DV1550
 *
 * A single-player memory game
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable:4996)

void shuffle(int arr[], int arrSize) /* This function shuffles all elements in the array arr[] */
{
	int randomNumb, temp;
	
	srand((unsigned int)time(NULL)); /* Initializes random number generator */

	for (int pos = 0; pos < arrSize; pos++)
	{
		randomNumb = rand() % 20;
		temp = arr[pos];
		arr[pos] = arr[randomNumb];
		arr[randomNumb] = temp;
	}
}

void printCards(int arr[], int taken[], int arrSize) /* This function prints the game board */
{
	printf("   0  1  2  3  4\n");
	printf("-|----------------\n");

	int row0 = 0, row1 = 0, row2 = 0, row3 = 0; /* Variables used to keep track of if the vertical numbering has yet been printed */

	for (int pos = 0; pos < arrSize; pos++)
	{
		if (pos >= 0 && pos < 5) /* Prints row 0 */
		{
			if (row0 == 0)
			{
				printf("0| ");
				row0++;
			}
			if (pos < arrSize - 15 && taken[pos] != 1)
			{
				printf("*  ");
			}
			else if (pos < arrSize - 15 && taken[pos] == 1)
			{
				printf("%d  ", arr[pos]);
			}
		}
		if (pos >= 5 && pos < 10) /* Prints row 1 */
		{
			if (row1 == 0)
			{
				printf("\n1| ");
				row1++;
			}
			if (pos < arrSize - 10 && taken[pos] != 1)
			{
				printf("*  ");
			}
			else if (pos < arrSize - 10 && taken[pos] == 1)
			{
				printf("%d  ", arr[pos]);
			}
		}
		if (pos >= 10 && pos < 15) /* Prints row 2 */
		{
			if (row2 == 0)
			{
				printf("\n2| ");
				row2++;
			}
			if (pos < arrSize - 5 && taken[pos] != 1)
			{
				printf("*  ");
			}
			else if (pos < arrSize - 5 && taken[pos] == 1)
			{
				printf("%d  ", arr[pos]);
			}
		}
		if (pos >= 15 && pos < 20) /* Prints row 3 */
		{
			if (row3 == 0)
			{
				printf("\n3| ");
				row3++;
			}
			if (pos < arrSize && taken[pos] != 1)
			{
				printf("*  ");
			}
			else if (pos < arrSize && taken[pos] == 1)
			{
				printf("%d  ", arr[pos]);
			}
		}
		if (pos < 0 || pos >= 20) /* Executes if the array size is incorrect */
		{
			printf("\nError. Incorrect array size!");	
		}
	}
}

void positionFinder(int selectRow, int selectCol, int *position, int *messageCode) /* This function finds the array position with input of row and column coordinates */
{
	if (selectRow == 0 && selectCol < 5 && selectCol >= 0 && *messageCode != 4) /* Executes if selected row == 0 and if selection is valid */
	{
		*position = selectCol;
		*messageCode = 1;
	}
	else if (selectRow == 1 && selectCol < 5 && selectCol >= 0 && *messageCode != 4) /* Executes if selected row == 1 and if selection is valid */
	{
		*position = selectCol + 5;
		*messageCode = 1;
	}
	else if (selectRow == 2 && selectCol < 5 && selectCol >= 0 && *messageCode != 4) /* Executes if selected row == 2 and if selection is valid */
	{
		*position = selectCol + 10;
		*messageCode = 1;
	}
	else if (selectRow == 3 && selectCol < 5 && selectCol >= 0 && *messageCode != 4) /* Executes if selected row == 3 and if selection is valid */
	{
		*position = selectCol + 15;
		*messageCode = 1;
	}
	else if (selectRow > 3 || selectRow < 0 || selectCol > 4 || selectCol < 0) /* Executes if selection is outside the board */
	{
		*position = -1; /* Mark position as invalid */
		*messageCode = 4;
	}
}

void checkGuess(int position1, int position2, int arr[], int taken[], int *messageCode) /* This function checks if the guess is valid and if a match has been found */
{
	if (position1 == position2) /* Executes if the player has chosen the same card twice */
	{
		*messageCode = 2;
	}
	else if (taken[position1] == 1 || taken[position2] == 1) /* Executes if the player has chosen a card that is taken */
	{
		*messageCode = 3;
	}
	else if (!(taken[position1] == 1 || taken[position2] == 1) && arr[position1] == arr[position2]) /* Executes if the player has found a match */
	{
		taken[position1] = 1;
		taken[position2] = 1;
		*messageCode = 5;
	}
}

void winCheck(int taken[], int arrSize, int *hasWon) /* This function checks if the user has yet matched all pairs */
{
	int amount = 0;

	for (int pos = 0; pos < arrSize; pos++)
	{
		if (taken[pos] != 1) /* Searches through taken[] to check how many cards are not taken */
		{
			amount++;
		}
	}

	if (amount == 0) /* Executes if all cards are taken */
	{
		*hasWon = 1;
	}
}

int main()
{
	int arr[20] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9};
	int taken[20];
	int arrSize = 20;
	
	int selectRow1, selectRow2;
	int selectCol1, selectCol2;
	int position1, position2;
	int hasWon = 0;
	int messageCode = 0;

	shuffle(arr, arrSize); /* Calls shuffle function */

	printf("Welcome to memory!\n\n");
	printCards(arr, taken, arrSize); /* Calls print function to print game board */


	while (hasWon == 0) /* Iterates as long as the user has not yet won */
	{
		if (messageCode == 0)
		{
			printf("\n\nFlip two cards!\n");

			printf("Input row and column for the first card: ");
			scanf("%d %d", &selectRow1, &selectCol1);
			positionFinder(selectRow1, selectCol1, &position1, &messageCode);

			printf("Input row and column for the second card: ");
			scanf("%d %d", &selectRow2, &selectCol2);
			positionFinder(selectRow2, selectCol2, &position2, &messageCode);

			if (position1 != -1 && position2 != -1) /* Executes only if the position is valid, i.e. inside the game board */
			{
				checkGuess(position1, position2, arr, taken, &messageCode);
			}
			
			getchar();
		}
		else if (messageCode == 1)
		{
			printf("Card1 is %d and card2 is %d.", arr[position1], arr[position2]);
			messageCode = 0;
		}
		else if (messageCode == 2)
		{
			printf("You have not chosen two different cards!");
			messageCode = 0;
		}
		else if (messageCode == 3)
		{
			printf("You have picked a card that is already taken!");
			messageCode = 0;
		}
		else if (messageCode == 4)
		{
			printf("You have picked a position outside the board!");
			messageCode = 0;
		}
		else if (messageCode == 5)
		{
			printf("You have a match!\n\n");
			printCards(arr, taken, arrSize);
			winCheck(taken, arrSize, &hasWon);
			
			if (hasWon == 0) /* Only executes when the user has not won */
			{
				messageCode = 0;
			}
		}
	}

	printf("\nBoard is solved. Game is over!");
	getchar();

	return 0;
}

