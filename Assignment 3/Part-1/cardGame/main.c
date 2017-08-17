// APS105 Assignment 3 Starter Code
// Jonathan Deber (deberjon) 991234567

// A card game simulator.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "histogram.h"

/* The number of cards in each suit. */
#define CARDS_PER_SUIT 13

/* The number of suits. */
#define NUM_SUITS  4

/* The number of cards in the deck. */
#define NUM_CARDS (CARDS_PER_SUIT * NUM_SUITS)

/* The values for each card in a suit. */
/* These values are for:                 A, 2, 3, 4, 5, 6, 7, 8, 9, 10,  J,  Q,  K */
const int CARD_VALUES[CARDS_PER_SUIT] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};

/* The number of symbols in a histogram row. */
#define HISTOGRAM_ROW_LENGTH 70

/* The symbol used to draw the histogram. */
#define HISTOGRAM_SYMBOL '*'

/* Our PRNG seed.  You can change the "1" to something else if you want to test other seeds, but do *not* modify the #ifndef or #endif lines. */
#ifndef PRNG_SEED
#define PRNG_SEED 1
#endif

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


/* Pseudorandomly generate a valid index into our deck of cards. */
int getRandomIndex(void);


/*
 * Begin Changes Here.
 */

// Add any new function prototypes here 

/*
 * End Changes Here.
 */




#ifndef CARDGAME_MAIN_DISABLED // This line is used by the auto-marker
int main(void)
{
    // Set up the PRNG
    srand(PRNG_SEED);

    /* Our deck of cards. */
    int deck[NUM_CARDS];
    
    
    /*
     * Begin Changes Here (Step 1).
     */
    
    // Initialize the deck in the format specified in the handout
     int i, j, k = 0;

     for (i = 0; i < NUM_SUITS; i++)
     {

         for (j = 0, k = k; j < CARDS_PER_SUIT; j++, k++)
         {
             *(deck + k) = *(CARD_VALUES + j);
         }
     }

    
    // Print out the deck for debugging purposes
    if (DEBUGGING)
    {
        for (i = 0; i < NUM_CARDS; i++)
        {
            printf("%d ", *(deck + i));
        }
    }

    
    /*
     * End Changes Here.
     */


    /*
     * Begin Changes Here (Step 2).
     */

    // Prompt for the number of hands
    int numHands;

    printf("Enter the number of hands: ");
    scanf("%d", &numHands);

    while(numHands <= 0)
    {
        printf("Number of hands must be greater than 0.\n");
        printf("Enter the number of hands: ");
        scanf("%d", &numHands);
    }

    /*
     * End Changes Here.
     */
     
     
    /*
     * Begin Changes Here (Step 3).
     */
    
    // Prompt for the number of cards per hand
    int numCardsPerHand;

    printf("Enter the number of cards per hand: ");
    scanf("%d", &numCardsPerHand);

    while(numCardsPerHand <= 0)
    {
        printf("Number of cards must be greater than 0.\n");
        printf("Enter the number of cards per hand: ");
        scanf("%d", &numCardsPerHand);
    }

    /*
     * End Changes Here.
     */
    

    /*
     * Begin Changes Here (Step 4).
     */
         
    /* The largest card value, which is the last element in CARD_VALUES. */
    int largestCard = *(CARD_VALUES + CARDS_PER_SUIT - 1);  // REPLACE THIS VALUE
    
    /* The largest possible score per hand. */
    int largestHand = largestCard * numCardsPerHand;  // REPLACE THIS VALUE

    /*
     * End Changes Here.
     */

    
    /* The number of occurrences of each possible score. */
    // Note: the value in index i corresponds to the number of occurrences of
    // the score i. The last index is therefore largestHand + 1. */
    int scoreOccurrences[largestHand + 1];


    /*
     * Begin Changes Here (Step 5).
     */
    
    // Initialize every element to 0, since we can't use an initializer with C99
    // Variable Length Arrays.
     for (i = 0; i <= largestHand; i++)
     {
         *(scoreOccurrences + i) = 0;
     }

     if (DEBUGGING)
    {
        for (i = 0; i <= largestHand; i++)
        {
            printf("%d ", *(scoreOccurrences + i));
        }
    }

    /*
     * End Changes Here.
     */    
    

    /*
     * Begin Changes Here (Step 6).
     */
        
    // Run our simulation numHands iterations
    for (i = 0; i < numHands; i++)
    {

        /* The total score of this hand. */
        int handTotal = 0;

        // Draw numCardsPerHand cards
        for (j = 0; j < numCardsPerHand; j++)
        {

            // Get a random index
            int index = getRandomIndex();
            
            // Get that card
            int cardDrawn = *(deck + index);
            
            // Print out debugging info about the card we drew

            // Add the card to our hand's total
            handTotal += cardDrawn;
        }

        // Print out debugging info about the total score

        // Now that we have a total score, record its occurrences
        ++*(scoreOccurrences + handTotal);
        
    }

    /*
     * End Changes Here.
     */ 


    /*
     * Begin Changes Here (Step 8).
     */
    
    // Print out the results in numeric form
    printf("Here are the results in numeric form:\n");
    for (i = 0; i <= largestHand; i++)
    {
        printf("%2d: %d\n", i, *(scoreOccurrences + i));
    }

    /*
     * End Changes Here.
     */ 

     
    /*
     * Begin Changes Here (Step 10).
     */
              
    // Print out the results as a histogram
    printf("Here are the results as a histogram:\n");

    char row[HISTOGRAM_ROW_LENGTH + 1];

    for (i = 0; i <= largestHand; i++)
    {
        /* The string to fill in with our histogram. */
        

        // Generate the histogram row
        int numSymbols = createHistogramRow(row, HISTOGRAM_SYMBOL, *(scoreOccurrences + i), numHands, HISTOGRAM_ROW_LENGTH);
        
        // And print it out
        printf("%2d:", i);
        for (j = 0; j < numSymbols; j++)
        {
            printf("%c", *(row + j));
        }

        printf("\n");
    }

    /*
     * End Changes Here.
     */ 

    return 0;
}
#endif // This line is used by the auto-marker



     
int getRandomIndex(void)
{
    /*
     * Begin Changes Here (Step 7).
     */
    int random = rand() % NUM_CARDS;
    
    return random; 
    
    /*
     * End Changes Here.
     */
}


/*
 * Begin Changes Here.
 */

// Add any new functions here 

/*
 * End Changes Here.
 */
