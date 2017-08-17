
// APS105 Assignment 3 Starter Code
// Jonathan Deber (deberjon) 991234567

// A helper function to help generate histograms.

#include "histogram.h"

#include <math.h>
#include <stdio.h>
#include <stdbool.h>

/* Should we print out extra debugging information? */
/* MUST be set to false prior to submission. */
#define DEBUGGING false
#define NULL_CHAR '\0'


int createHistogramRow(char row[], char symbol, int value, int maxValue, int maxRowLength)
{
    /*
     * Begin Changes Here (Step 9).
     */
     
    // Figure out how many symbols we need to use
    int i;
    int n = round(((double)value / maxValue) * maxRowLength);
    
    // Write the appropriate number of symbols into row
    for (i = 0; i < n; i++)
    {
        *(row + i) = symbol;
    }
       
    // Add a trailing \0
    *(row + n) = NULL_CHAR;
    
    // Return the number of symbols we wrote

    return n; 
    
    
    /*
     * End Changes Here.
     */
    
}
