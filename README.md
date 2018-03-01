# DynamicMatrix
A repository containing two C programs. 

verify_hetero.c
This program will read in a text file for a square matrix and perform operations on it to verify if the matrix has duplicates when adding the diagonals, rows, and columns. If there are any duplicates, the matrix is not a hetero-matrix. 

generate_magic.c
This program will generate a square matrix based on the size given by the user. The matrix created will have diagonals, row, and columns all sum to the same value. In practice, it should cause verify_hetero.c to return false.

Both programs utilize dynamic memory allocation for the 2D square arrays. 
