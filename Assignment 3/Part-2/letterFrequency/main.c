// APS105 Assignment 3 Starter Code
// Jonathan Deber (deberjon) 991234567

// A letter frequency counter.

#include <stdio.h>

#include "histogram.h"

/* The list of possible letters.  Note that although this is a char[], it is not a string, since it is not null terminated. */
const char LETTERS[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

/* The number of possible letters.  Note that we calculate this based on the contents of LETTERS, so that this value is automatically updated if the contents of LETTERS were to change. */
#define NUM_LETTERS (sizeof(LETTERS) / sizeof(char))

/* Special index used to indicate that a letter was not found in LETTERS. */
#define LETTER_NOT_FOUND -1

/* The max length of text we can handle.  Additional characters are silently ignored. */
#define TEXT_MAX_LENGTH 1024

/* The maximum number of symbols in one histogram row. */
#define HISTOGRAM_ROW_LENGTH 55

/* The symbol used to draw the histogram . */
#define HISTOGRAM_SYMBOL '-'

/* Should we print out extra debugging information? */
/* MUST be set to false prior to submission. */
#define DEBUGGING false


/*
 * Begin Changes Here.
 */

// Add any new constants here 

/*
 * End Changes Here.
 */


/* Function Declarations. */

/* Returns the index in LETTERS that corresponds to the letter 'letter', or LETTER_NOT_FOUND if 'letter' does not occur in LETTERS. */
int letterToIndex(char letter);


/*
 * Begin Changes Here.
 */

// Add any new function prototypes here 
void printHistogram (int i, int numSymbols, char *row);

int countMaxValue (int *occurrences);
/*
 * End Changes Here.
 */



#ifndef LETTERFREQUENCY_MAIN_DISABLED // This line is used by the auto-marker
int main(void)
{
    /*
     * Begin Changes Here (Step 11).
     */
    
    // Print out our prompt
    printf("Enter some text (characters other than lowercase letters will be ignored): ");
    
    // Allocate a buffer to hold the user input
    char input[TEXT_MAX_LENGTH + 1];
    
    // Read in our sequence, using fgets()
    fgets(input, TEXT_MAX_LENGTH + 1, stdin);

    /*
     * End Changes Here.
     */

    /*
     * Begin Changes Here (Step 12).
     */
    
    // Create an array to hold the occurrences of each letter.  The indices correspond to the indices of LETTERS.
    int countOccurrences[NUM_LETTERS] = {0};
    
    // Process the user's text until we run out of characters 
    char *p;
    for (p = input; (*p != '\0') && (*p != '\n'); p++)
    {
            
        // Convert our letter to an array index
        int index = letterToIndex(*p);

        // If it's a valid index, then we want to count it
        if (index != LETTER_NOT_FOUND)
        {
            ++*(countOccurrences + index);
        }

        // Otherwise, skip it and print a message
        else
        {
            printf("Skipping non-lowercase letter: '%c'.\n", *p);
        }
    }

    /*
     * End Changes Here.
     */

    /*
     * Begin Changes Here (Step 14).
     */
    
    // Print out the numeric results
    int i;

    printf("Here are the results in numeric form:\n");

    for (i = 0; i < NUM_LETTERS; i++)
    {
        printf("%c: %d\n", *(LETTERS + i), *(countOccurrences + i));
    }

    // Generate and print out the histogram
    printf("Here are the results as a histogram:\n");
    
    char row[HISTOGRAM_ROW_LENGTH + 1];

    for (i = 0; i < NUM_LETTERS; i++)
    {
        /* The string to fill in with our histogram. */
        
        // Generate the histogram row
        int maxValue = countMaxValue (countOccurrences);
        int numSymbols = createHistogramRow(row, HISTOGRAM_SYMBOL, *(countOccurrences + i), maxValue, HISTOGRAM_ROW_LENGTH);
        
        // And print it out
        printHistogram (i, numSymbols, row);
    }
    
    /*
     * End Changes Here.
     */
    
    return 0;
}
#endif // This line is used by the auto-marker


int letterToIndex(char letter)
{

    /*
     * Begin Changes Here (Step 13).
     */
    
    // Go through each letter in LETTERS, and see if it's a match
    int i;

    for (i = 0; i < NUM_LETTERS; i++)
    {
        if (letter == *(LETTERS + i))
        {
            return i;
        }
    }

    return LETTER_NOT_FOUND;
    
    /*
     * End Changes Here.
     */
}

/*
 * Begin Changes Here.
 */

// Add any new functions here 
void printHistogram (int i, int numSymbols, char *row)
{
    int j;

    printf("%c:|", *(LETTERS + i));

    for (j = 0; j < numSymbols; j++)
    {
        printf("%c", *(row + j));
    }

    printf("|\n");
}

int countMaxValue (int *occurrences)
{
    int i, sum = 0;

    for (i = 0; i < NUM_LETTERS; i++)
    {
        sum += *(occurrences + i);
    }

    return sum;
}

/*
 * End Changes Here.
 */
