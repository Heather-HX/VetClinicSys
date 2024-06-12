/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3

/////////////////////////////////////////////////////////////////////////*/

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H
#define CORE_H

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// Copy your work done from Milestone #2 (core.h) into this file
// 
// NOTE:
// - Organize your functions into the below categories
// - Make sure the core.c file also lists these functions in the same order!
// - Be sure to provide a BRIEF comment for each function prototype
// - The comment should also be copied to the core.c function definition
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//Reads a whole number from user input.
int inputInt(void);

//Gets a positive integer from user input.
int inputIntPositive(void);

//Requests an integer within a specified range.
int inputIntRange(int lowerBound, int upperBound);

//Reads a single character from a set of valid options.If the input is more than one character or not a valid option,
//  it prompts the user again.
char inputCharOption(const char strArr[]);

//Inputs a string within a specified length range.
void inputCString(char* str, int min, int max);

//Formats and displays a 10-digit phone number.
void displayFormattedPhone(const char* number);



// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H
