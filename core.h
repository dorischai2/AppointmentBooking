

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H
#define CORE_H

#define MAX_STR_LEN 1200

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

// Display phone number if a phone number c-string is given, otherwise display empty phone format
void displayFormattedPhone(const char cStr[]);

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Return a user-input integer value
int inputInt(void);

// Return a user-input positive integer value
int inputIntPositive(void);

// Return a integer value within given range (inclusive)
int inputIntRange(int lowerBound, int upperBound);

// Return a valid user-input char based on given C-String which represents the list of valid chars
char inputCharOption(const char cStr[]);

// Get a valid user input C-String with length between min and max (inclusive)
void inputCString(char cStr[], int min, int max);


// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H
