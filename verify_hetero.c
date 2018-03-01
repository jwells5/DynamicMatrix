////////////////////////////////////////////////////////////////////////////////
// Main File:        verify_hetero.c
// This File:        verify_hetero.c
// Other Files:      (name of all other files if any)
// Semester:         CS 354 Spring 2018
//
// Author:           Jonas Wells
// Email:            jwells5@wisc.edu
// CS Login:         jonas
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          
//                   
//
// Online sources:  www.tutorialspoint.com/c_standard_library/
//			Helped with understanding the needed functions for the 
//			program.   
//                    
//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure representing Square
// size: dimension(number of rows/columns) of the square
// array: 2D array of integers
typedef struct _Square {
    int size;
    int **array;
} Square;

Square * construct_square(char *filename);
int verify_hetero(Square * square);
void insertion_sort(int* arr, int size);

/* Main Function -- the execution of the entire program is done here.
 *
 * argc -- The first argument which contains the program name.
 * argv -- The second argument which is used to hold the file.
 * Returns 0 when the program finishes executing correctly.
 */
int main(int argc, char *argv[]) {                        

	//The file from the user. Stored as a char pointer.
	char *f = argv[1];

	if (argv[1] == NULL) {
		printf("Usage: ./verify_hetero <filename>\n");
		exit(1);
	}		
    // Check input arguments to get filename
	// The square that will be constructed
	Square *test = construct_square(f);
	
    // Construct square

	verify_hetero(test);
	
    // Verify if it's a heterosquare and print true or false
//	test->size = sizeTest;
//	test->array = a;
	
	for (int i = 0; i < test->size; i++) {
		free(*(test->array+i));   //array[i]);
	}
	free(test->array);
	
	return 0;
}

/* This function is responsible for the construction of the square through the use of the square struct. 
 *
 * filename -- This argument is the input file that will be used to build the square.
 * Returns the fully constructed square.
 */
Square * construct_square(char *filename)  {               
	//The file that the information will be gathered from. Will be of type File.
	FILE *fp;
	fp = fopen(filename, "r");

	if(fp == NULL) {
		printf("Cannot open file for reading.\n");
		exit(1);
	}
	//Size gathered from the first line of the file. Will be of type int.
	int size;	
//	int num;	
	//Used to tokenize the string and access the matrix. Will be an array of chars.
	char buf[100];
	//Pointer to hold the values in the file. Will be a char pointer.
	char *value;
/*
	if(fgets(buf, sizeof(buf), fp) == NULL) {
		printf("Null pointer when trying to access the elements of the file\n");
		exit(1);
	}

	if(atoi(strtok(buf, ",")) == 0) {
		printf("No valid converstion of variables could be performed\n");
	}
 
*/
	
	if(fgets(buf, sizeof(buf),fp) == NULL) {
		printf("fgets() returns a null pointer.\n");
		exit(1);
	}

	size = atoi(strtok(buf, ","));
	if(size == 0) {
		printf("No valid conversion could be performed.\n");
		exit(1);
	}
/*

	if(fp != NULL) {
		fgets(buf, sizeof(buf), fp);
		size = atoi(strtok(buf, ","));	

		
	}

*/
//	printf("%d\n", size);	
	//The array used to construct the square. Will be a 2D array of int pointers.
	int **m;
	m = malloc(sizeof(int*) * size);

	if(m == NULL) {
		printf("The request for memory has failed.\n");
		exit(1);
	}

	for (int i = 0; i < size; i++) {
		*(m+i) = malloc(size * sizeof(int));
		if(*(m+i) == NULL) {
			printf("The request for memory has failed.\n");
			exit(1);
		}
	}	



	if(sizeof(Square) == 0) {
		printf("The sizeof(Square) is returning 0\n");
		exit(1);
	}	

	Square *temp = malloc(sizeof(Square));

	if(temp == NULL) {
		printf("The request for memory has failed.\n");
		exit(1);
	}

	temp->size = size;
	temp->array = m;



	for (int i = 0; i < size; i++) {
		if(fgets(buf, sizeof(buf), fp ) == NULL) {
			printf("fgets() returns a null pointer.\n");
			exit(1);

		} else {

		//fgets(buf, sizeof(buf), fp);
		value = strtok(buf, ",");
		if(value == NULL) {
			printf("strtok() is returning a null value indicating there are no more tokens to retrieve. This is not the case.\n");
			exit(1);
		}	

			for (int j = 0; j < size; j++) {

				*(*(m+ i)+j) = atoi(value);

				if(atoi(value) != 0 && *(*(m+i)+j) == 0) {
					printf("atoi() is returning 0 which means no valid conversion could be performed.\n");
					exit(1);
				}

				if(j != (size - 1)) {
					value = strtok(NULL, ",");
				}
				
				if(value == NULL) {
					printf("strtok() is returning a null value indiciating there are no more tokens to retrieve. This is not the case.\n");
					exit(1);
				}
				
			}
	
		}
	//Do I need to check for null characters when adding to array from file?
	}
	 




	if(fclose(fp) == EOF) {
		printf("File stream could not be closed\n");
		exit(1);
	}
    
    
    // Open and read the file

    // Read the first line to get the square size

    // Initialize a new Square struct of that size

    // Read the rest of the file to fill up the square
	return temp;

}

/* verify_hetero verifies if the square is a heterosquare
 * 
 * square -- This argument is the square to be verified.
 * Returns 1(true) or 0(false).
 */
int verify_hetero(Square * square) {               

	//size of the square. Will be of type int.
  	int sizeVis = square->size;
	//array to help verify values. Will be a 2D array of type int.
  	int **newM = square->array;
 	
	//Each of the following variables will the hold the 8 needed values for verification. Will of type int.
  	int sumCol = 0;
  	int sumRow = 0;
 	int mainDiag = 0;
	int secDiag = 0; 

	//The index of the array and the array to hold the above values. Will be of type int.
	int index = 0;
	int a[sizeVis*2 + 2];
//  int *a;
//  a = malloc(sizeof(int) * (sizeVis*2 + 2));

	//each of the following for-loops are responsible for adding up the required values
	for (int i = 0; i < sizeVis; i++) {
		for (int j = 0; j < sizeVis; j++) {
			sumRow  = sumRow + *(*(newM+i)+j); 
		}
		a[index] = sumRow;
//			fprintf("%d\n", sum);
		sumRow = 0;
		index = index + 1;  

//	printf("%d, ", a[index]);
	}
//	printf("%d, ", a[index]);


	for (int j = 0; j < sizeVis; j++) {
		for (int i = 0; i < sizeVis; i++) {
			sumCol = sumCol + *(*(newM+i)+j);	
		}
		a[index] = sumCol;

		sumCol = 0;
		index = index + 1;

//	printf("%d, ", a[index]);
	}



	for (int i = 0; i < sizeVis; i++) {
		
		mainDiag = mainDiag + *(*(newM+i)+i);

		secDiag = secDiag + *(*(newM+i)+(sizeVis-i-1));
	}

	a[index] = mainDiag;
	index = index + 1;
	a[index] = secDiag;

/*
		for (int x = 0; x < 8; x++) {
			printf("%d , ", a[x]);
		}
//	printf("%d", sizeof(a));	
*/
	if(sizeof(a[0]) == 0) {
		printf("Division by zero! Aborting...\n");
	}

   	insertion_sort(a, sizeof(a)/sizeof(a[0]));

/*
		printf("\n");
		
		for (int x = 0; x < 8; x++) {
			printf("%d , ", a[x]);
		}

*/
	//calculates the length of the array
	int array_size = sizeof(a) / sizeof(a[0]);

/*
	for (int i = 0; i < array_size; i++) {
		if (a[i] == a[i+1]) {
			printf("false");
			return 1;
		}
		
	}

//	printf("true");
*/
	//checks for duplicates indexing through the sorted array
	for (int i = 0; i < array_size; i++) {
		if (a[i] == a[i+1]) {
			printf("false\n");
			return 0;
		} else {
			printf("true\n");
			return 1;
			}
	}

/*

	for (int i = 0; i < array_size; i++) {
		for (int j = i+1; i < array_size; i++) {
			//will j overflow?

			printf("\n%d", a[i]);
                        printf("\n%d", a[j]);

			if (a[i] == a[j]) {
				printf("\n%d", a[i]);
				printf("\n%d", a[j]);
				printf("false\n");
				return 1;
				//printf("true");
			} else if (a[i] == array_size) {
				printf("true\n");
				return 0;
				//printf("false");
			}
		}
	}

*/
	//is it size of int or size of char?

	// can I pass the variable size out of the above method?

    // Calculate sum of the following and store it in an array
    // all rows and cols
    // main diagonal
    // secondary diagonal

    // Pass the array to insertion_sort function

    // Check the sorted array for duplicates

	return 0;
}

/* insertion_sort sorts the arr in ascending order
 * 
 * arr -- The first argument is the array to be sorted.
 * size -- The second argument is the length of the array.
 * There is no return value, but the array will be sorted.
 */
void insertion_sort(int* arr, int size) {                 

	int i;
	int j;

	for (i = 0; i < size; i++) {
		j = i;
		//This while loop performs the insertion sort
		while(j > 0) {
			if (arr[j-1] > arr[j]) {
				int temp = arr[j-1];
				arr[j-1] = arr[j];
				arr[j] = temp;
			} else {
				break;
			}
			j--;
		}
	}

	// Sort the arr
}
