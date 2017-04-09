#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Assigned by:
 Guy Agiv ID#203507926
*/

#define WALL 2 // Security Wall
#define R 100 // Rows
#define C 100 //	Cols

typedef int matrix[R + WALL][C + WALL];

//Function Declartions
void random_insertion_matrix(matrix, int , int );
void manual_insertion_matrix(matrix, int , int );
void printing_matrix(matrix, int , int );
int Checking_Neighbors(matrix, int , int );
void copy_matrix(matrix, matrix, int , int );
int compare_matrix(matrix, matrix, int , int );
void dead_or_alive(matrix, matrix,int, int);

//================================================
void main()
{

	matrix mat = { -4 };
	matrix temp_matrix = { -4 };
	int rows, cols, choose;
	int result, key;

	printf("Welcome to the game of life!\n\n\n");
	printf("Enter please rows and cols of the matrix(Max input can be 100X100):\n");
	scanf("%d %d", &rows, &cols);
	
	printf("Ok press '1' for random insertion or '0' for manual insertion:\n");
	scanf("%d", &choose);
	switch (choose)
	{
	case 1:{ random_insertion_matrix(mat, rows, cols); break; }
	case 0:{manual_insertion_matrix(mat, rows, cols); break; }
	default: {printf("Wrong choose!\n"); exit(0); }
	}

	printing_matrix(mat, rows, cols); // Printing First Original Matrix

	do
	{
		dead_or_alive(mat, temp_matrix, rows, cols);
		printing_matrix(temp_matrix, rows, cols);
		result = compare_matrix(mat, temp_matrix, rows, cols);

		if (result == 0)
		{
			printf("Game over ! both matrices are even.\n");
			exit(0);
		}
		else
		{
			printf("Do you want to continue? Press 0 for exit or any other number to continue\n");
			scanf("%d", &key);
		}
		if (key != 0)
			copy_matrix(mat, temp_matrix, rows, cols);
	}
	while (key);
}
void random_insertion_matrix(matrix m, int r, int c) // If the guest chose a random insertion
{
	int i, j;
	srand(time(NULL));
	for (i = 1; i <= r; i++)
	{
		for (j = 1; j <= c ; j++)
			m[i][j] = rand() % 2;
	}
}

void manual_insertion_matrix(matrix m, int r, int c) // If the guest chose a manual insertion
{
	int i, j;
	for (i = 1; i <= r; i++)
	{
		for (j = 1; j <= c ; j++)
		{
			printf("Enter number to slot:[%d][%d]\n", i, j);
			scanf("%d", &m[i][j]);
		}
	}
}
void printing_matrix(matrix m, int r, int c) // Printing matrix
{
	int i, j;
	char star = '*', slash = '/';
	for (i = 1; i <= r ; i++)
	{
		for (j = 1; j <= c; j++)
		{
			if (m[i][j] == 0)
				printf("%4c", slash);
			else
				printf("%4c", star);
		}
		putchar('\n');
	}
	printf(" * = Alive\n / = Dead\n");
}

int Checking_Neighbors(matrix m, int current_r, int current_c) // Checking to current slot his eight neighbors around him
{
	int counter = 0;

	if (m[current_r][current_c - 1] ==1) // left side
		counter++;
	if (m[current_r][current_c + 1] ==1) //right side
		counter++;
	if (m[current_r - 1][current_c] ==1) // up
		counter++;
	if (m[current_r + 1][current_c] ==1) // down
		counter++;
	if (m[current_r + 1][current_c + 1] ==1) // right down diagonal
		counter++;
	if (m[current_r - 1][current_c - 1] ==1) // left up diagonal
		counter++;
	if (m[current_r - 1][current_c + 1] ==1) // right up diagonal
		counter++;
	if (m[current_r + 1][current_c - 1] ==1) // left down diagonal
		counter++;
	return counter;
}

void copy_matrix(matrix m, matrix m_2, int r, int c) // Copying from matrix 2 to matrix 1
{
	int i, j;
	for (i = 1; i <= r; i++)
	{
		for (j = 1; j <= c; j++)
			m[i][j] = m_2[i][j];
	}
}

int compare_matrix(matrix m, matrix m_2, int r, int c) // Comparing between first matrix and temp matrix to see if the game is over
{
	int i, j;
	for (i = 1; i <= r; i++)
	{
		for (j = 1; j <= c; j++)
		{
			if (m[i][j] != m_2[i][j])
				return 1;
		}
	}
	return 0;
}

void dead_or_alive(matrix mat,matrix temp_matrix ,int rows, int cols) // Changing status to each slot according to the amount of his neighbors
{
	int i, j, num_of_neighbors;
	for (i = 1; i <= rows; i++)
	{
		for (j = 1; j <= cols; j++)
		{
			num_of_neighbors = Checking_Neighbors(mat, i, j); // Sending to function to check if the neighbors of current cell alive / dead
			if (mat[i][j] == 1) // If the current slot is alive
			{
				if (num_of_neighbors <= 1 || num_of_neighbors >= 4)
					temp_matrix[i][j] = 0; // Changing the current slot  to be a dead (odd number)
				else
					temp_matrix[i][j] = 1;
			}
			if (mat[i][j] == 0)
			{
				if (num_of_neighbors == 3)
					temp_matrix[i][j] = 1;
				else
					temp_matrix[i][j] = 0;
			}
		}
	}
}