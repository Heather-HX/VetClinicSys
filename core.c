/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3

/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>
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


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file


int inputInt(void)
{
    int getInt;
    char newL;
    int isValidInput;
    do
    {
        isValidInput = 1;
        scanf("%d%c", &getInt, &newL);
        if (newL != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
            isValidInput = 0;
        }
    } while (!isValidInput);

    return getInt;
}

int inputIntPositive(void)
{
    int getInt, valid;
    do
    {
        valid = 1;
        getInt = inputInt();
        if (getInt <= 0)
        {
            valid = 0;
            printf("ERROR! Value must be > 0: ");
        }
    } while (!valid);
    return getInt;
}

int inputIntRange(int lowerBound, int upperBound)
{
    int getInt, valid;
    do
    {
        valid = 1;
        getInt = inputInt();
        if (getInt < lowerBound || getInt > upperBound)
        {
            valid = 0;
            printf("ERROR! Value must be between %d and %d inclusive: ", lowerBound, upperBound);
        }
    } while (!valid);
    return getInt;
}

char inputCharOption(const char strArr[])
{
    char sinC, extraChar;
    int i, validInput;
    do
    {
        validInput = 1; // 假设输入是有效的，直到证明其无效
        scanf(" %c", &sinC);

        // 检查输入缓冲区是否还有额外的字符
        while ((extraChar = getchar()) != '\n' && extraChar != EOF)
        {
            validInput = 0; // 发现额外的输入
        }

        // 检查sinC是否为有效字符
        for (i = 0; strArr[i] != '\0' && validInput; i++)
        {
            if (sinC == strArr[i])
            {
                validInput = 1; // 找到有效字符，跳出循环
            }
        }

        if (!validInput)
        {
            printf("ERROR: Character must be one of [%s]: ", strArr);
        }
    } while (!validInput);
    return sinC;
}

void inputCString(char* str, int min, int max)
{

    int length;
    char getInput[999 + 1] = { 0 };
    char fmt[20 + 1] = { '\0' };
    do
    {
        sprintf(fmt, "%%%d[^\n]", max + 2);
        scanf(fmt, getInput);
        clearInputBuffer();

        length = strlen(getInput);

        if (min == max && (length > max || length < min))
        {
            printf("ERROR: String length must be exactly %d chars: ", min);
        }
        else if (length > max)
        {
            printf("ERROR: String length must be no more than %d chars: ", max);
        }
        else if (length < min)
        {
            printf("ERROR: String length must be between %d and %d chars: ", min, max);
        }

    } while (length > max || length < min);

    strcpy(str, getInput);
}



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

void displayFormattedPhone(const char* number)
{
    int len = 0;

    while (number != '\0' && isdigit(number[len]))
    {
        len++;
    }

    if (len == 10)
    {
        printf("(%.3s)%.3s-%.4s", &number[0], &number[3], &number[6]);
    }
    else
    {
        printf("(___)___-____");
    }
}