

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "core.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}

// Display phone number if a phone number c-string is given, otherwise display empty phone format
void displayFormattedPhone(const char cStr[])
{
    int i = 0, j = 0;

    if (cStr == NULL || cStr[0] == '\0')
    {
        printf("(___)___-____");
    }
    else
    {
        for (i = 0; cStr[i] != '\0'; i++)
        {
            if (isdigit(cStr[i]))
            {
                j++;
            }
        }

        if (i == 10 && j == 10)
        {
            printf("(%.3s)%.3s-%.4s", cStr, &cStr[3], &cStr[6]); 
        }
        else
        {
            printf("(___)___-____");
        }
    }
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Return a user-input integer value 
int inputInt(void)
{
    int num;
    char newLine = '\0';
    int valid;
    
    do {
        valid = 1;
        scanf("%d%c", &num, &newLine);
       
        if (newLine != '\n')
        {
            clearInputBuffer();
            valid = 0;
            printf("Error! Input a whole number: ");
        }
    } while (!valid);

    return num;
}

// Return a user-input positive integer value
int inputIntPositive(void)
{
    int num, valid;
    do {
        valid = 1;
        num = inputInt();
        if (num <= 0)
        {
            valid = 0;
            printf("ERROR! Value must be > 0: ");
        }
    } while (!valid);

    return num;
}

// Return a integer value within given range (inclusive)
int inputIntRange(int lowerBound, int upperBound)
{
    int num, valid;
    do {
        valid = 1;
        num = inputInt();
        if (num < lowerBound || num > upperBound)
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", lowerBound, upperBound);
            valid = 0;
        }
    } while (!valid);

    return num;
}

// Return a valid user-input char based on a given C-String which represents the list of valid chars
char inputCharOption(const char cStr[]) 
{
    char* match = NULL;
    char charInput = '\0', newLine = '\0';
    int i;

    do {
        match = 0;
        scanf("%c%c", &charInput, &newLine);

        if (newLine != '\n')
        {
            clearInputBuffer();
            printf("ERROR: Character must be one of [%s]: ", cStr);
        }
        else
        {
            match = strchr (cStr, charInput); 
            
            // if (match != NULL)
            // {
            //     match = 1;
            // }
            
            if (match == NULL)
            {
                printf("ERROR: Character must be one of [");
                for (i = 0; cStr[i] != '\0'; i++)
                {
                    printf("%c", cStr[i]);
                }
                printf("]: ");
            }
        }
    } while (match == NULL);
    
    return charInput;
}

// Get a valid user input C-String with length between min and max (inclusive)
void inputCString(char cStr[], int min, int max)
{
    char inputCStr[MAX_STR_LEN + 1] = { '\0' };
    char fmt [20 + 1] = { '\0' };
    int inputCStrLen, valid;

    sprintf(fmt, "%%%d[^\n]", MAX_STR_LEN);
    
    do {
        valid = 1;
        scanf(fmt, inputCStr);
        clearInputBuffer();

        inputCStrLen = strlen(inputCStr);
        
        if (inputCStrLen < min || inputCStrLen > max)
        {
            valid = 0;
            if (min == max)
            {
                printf("ERROR: String length must be exactly %d chars: ", min);
            }
            else if (inputCStrLen < min)
            {
                printf("ERROR: String length must be between %d and %d chars: ", min, max);
            }
            else
            {
                printf("ERROR: String length must be no more than %d chars: ", max);
            }
        }
        else
        {
            strcpy(cStr, inputCStr);
        }
    } while (!valid);
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////


