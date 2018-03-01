////////////////////////////////////////////////////////////////////////////////
// Main File:        generate_magic.c
// This File:        generate_magic.c
// 
// Semester:         CS 354 Spring 2018
//
// Author:           Jonas Wells
// Email:            jwells5
// CS Login:         jonas
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   www.tutorialspoint.com/c_standard_library/
//                    
//                   
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

// Structure representing Square
// size: dimension(number of rows/columns) of the square
// array: 2D array of integers
typedef struct _Square {
    int size;
    int **array;
} Square;

int get_square_size();
Square * generate_magic(int size);
void write_to_file(char *filename, Square * square);

/*
 * Main Function -- responsible for the execution of the program.
 *
 * argc -- First argument responsible for which program to be executed.
 * argv -- This is the input file to be written to.
 * Returns 0 when the program executes correctly
 */
int main(int argc, char *argv[])                 
{
	// Will hold the file to be written to. Will be a char pointer.
	char* f = argv[1];

	if(argv[1] == NULL) {
		printf("Usage: ./generate_magic <filename>\n");
		exit(1);
	}

    // Check input arguments to get filename
	int result = get_square_size();
    // Get size from user
	

	Square *temp = generate_magic(result);
    // Generate the magic square
	write_to_file(f, temp);
    // Write the square to the output file

	if(temp->array == NULL) {
		printf("The Square is NULL so attempting to free will cause undefined behavior. We will abort instead.\n");
		exit(1);
	}
	

	for (int i = 0; i < temp->size; i++) {
                free(*(temp->array+i));   //array[i]);
	}
 
        free(temp->array);


	return 0;
}

/* get_square_size is responsible for getting the size from user input. 
 *
 * Returns the user input.
 */
int get_square_size()            
{
	// The size from user. Will be of type int.
	int a;
		
	printf("Enter size of magic square, must be odd\n");
	scanf("%d", &a);

	if(a < 0) {
		printf("scanf() returned a negative number, which means the function did not work as intended or the user did not follow directions.\n");
		exit(1); 
	}
	
	if(a < 3) {
		printf("Size must be an odd number >= 3.\n");
		exit(0);
	}

	if((a % 2) == 0) {
		printf("Size must be an odd number >= 3.\n");
		exit(0);
	}

	return a;
}

/* generate_magic constructs a magic square of size n using the Siamese algorithm and returns the Square struct
 * 
 * n -- This argument is the size of the square to be constructed.
 * Returns the square after construction.
 */
Square * generate_magic(int n)           
{
	//Array for the square. Will be a 2D array of type int.	
	int **t;
        t = malloc(sizeof(int*) * n);
		if(t == NULL) {
			printf("The request for memory has failed.\n");
			exit(1);
		}


        for (int i = 0; i < n; i++) {
                *(t+i) = malloc(n * sizeof(int));

		if(*(t+i) == NULL) {
			printf("The request for memory has failed.\n");
			exit(1);
		}
        }

	for(int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			*(*(t+i)+j) = 0;
		//	t[i][j] = 0;
		}
	}		
	//The middle of the array. Will be of type int.
	int i = n/2;
	//Length of array minus one. Will be of type int.
	int j = n - 1;
	
	for (int num = 1; num <= n*n; ) {
		if (i == -1 && j ==n) {
			j = n - 2;
			i = 0;		
		} else {
			if (j == n) {
				j = 0;
			}
			if (i < 0) {
				i = n - 1;
			}
		
		if (*(*(t+i)+j)) {
			j -= 2;
			i++;
			continue;	
		} else {
			*(*(t+i)+j) = num++;
	//		t[i][j] = num++;
			j++;
			i--;
		}
		}
	}
	//The pointer to the square
	Square *temp = malloc(sizeof(Square));
	if (temp == NULL) {
		printf("The request for memory for the Square has failed.\n");
		exit(1);
	}

	temp->size = n;
	temp->array = t;

/*
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d, ", t[i][j]);
		}
		printf("\n");
	}	
*/
	return temp;

}

/* write_to_file opens up a new file(or overwrites the existing file) and writes out the square in the format expected by verify_hetero.c
 *
 * filename -- The file to be written to.
 * square -- The square that is going to be written to the file.
 */
void write_to_file(char *filename, Square * square)              
{	
	//File to be written to. Will be of type File
	FILE *fp;
	fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}
	//Size of the square. Will be of type int.
	int size = square->size;
	//The array to be used. Will be a 2D pointer variable with int's
	int **arr = square->array;
//	printf("%d ", size);

	
	if(fprintf(fp,"%d\n", size) < 0) {
		printf("Printing to file returned a negative number indicating it was not successful.\n");
		exit(1);
	}
//	fwrite(&size, 4,1, fp);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (j == size - 1) {	
				if(fprintf(fp, "%d", arr[i][j]) < 0) {
					printf("Printing to file returned a negative number indicating it was not successful.\n");
					exit(1);
				}
			} else {
				if(fprintf(fp, "%d,", arr[i][j]) < 0) {
					printf("Printing to file returned a negative number indicating it was not successful.\n");
					exit(1);
				}
			}
		}		
		if(fprintf(fp, "\n") < 0) {
			printf("Printing to file returned a negative number indicating it was not successful.\n");
			exit(1);
		}
	}
//	fwrite(&square, sizeof(square), 1, fp);

//	return fp;


	if(fclose(fp) == EOF) {
		printf("File closing was unsuccessful.\n");
		exit(1);
	}

    // Write the square to file
}	
