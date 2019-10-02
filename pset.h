// pset.h

#ifndef PSET_H
#define PSET_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Read the standard input file,
// Convert the value of each cell,
// Make an array and return it.
int** read_input(int*, int*);

// Print the Array of N rows and M columns.
void print_board(int ,int , int**);

// Execute the z3,
// Make a new array containing result.
// If solution that satisfies the formula exists, return true,
// Otherwise return false.
bool z3(int,int,int**);

#endif