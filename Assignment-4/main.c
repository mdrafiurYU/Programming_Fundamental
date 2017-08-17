// APS105 Assignment 4 Starter Code
// Jonathan Deber (deberjon) 991234567

// A simple guest list manager

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Initial size of the lists. */
#define GUEST_LIST_INITIAL_SIZE    3
#define ACCEPTED_LIST_INITIAL_SIZE 2

/* Amount we increase the length each time we grow the lists. */
#define GUEST_LIST_INCREMENT_SIZE    3
#define ACCEPTED_LIST_INCREMENT_SIZE 2

/* Top level menu commands. */
#define MENU_ADD    "add"
#define MENU_DELETE "delete"
#define MENU_PRINT  "print"
#define MENU_ACCEPT "accept"
#define MENU_QUIT   "quit"

/* "yes" and "no" responses. */
#define CMD_YES     "yes"
#define CMD_NO      "no"

/* Sizes of our string buffers. */
#define CMD_MAX_LENGTH  10  /* Menu commands. */
#define NAME_MAX_LENGTH 50  /* Guest names. */

/* Text that is added to a person's name if they have an additional guest. */
#define TEXT_PLUS_GUEST " + guest"

/* Should we print out extra debugging information? */
/* MUST be set to false prior to submission. */
#define DEBUGGING true


/*
 * Begin Changes Here.
 */

// Add any new constants here 

/*
 * End Changes Here.
 */
 
/* Function Declarations. */

/* Prints out the contents of 'list', which is an array of strings of size 'n'. */
void printList(char *list[], int n);


/* Continually prompts the user until they enter a row number between 0 and 'maxRow'.*/
int getValidRow(int maxRow);

/* Continually prompts the user to enter "yes" or "no" to indicate if a person will be 
 * bringing an additional guest.  Returns true if the user has entered "yes", false if 
 * they have entered "no".*/
bool getIsExtraGuest(void);

/* Prompts the user to enter a name (maximum of NAME_MAX_LENGTH characters).  getName()
 * then allocates a new string to hold the name, and copies the user's input into that 
 * string.  The new string is sized so that it exactly fits the user's input (plus a null
 * character).  Returns a pointer to that string.  It is the caller's responsibility to 
 * free() the string when it is no longer needed. */
char *getName(void);


/* Adds the specified name to 'guestList' (an array of strings of size '*n').  'name' will
 * be added to the first available space in 'guestList', which may be in the middle of the
 * array.  If 'guestList' does not have any available space, we realloc() the array to 
 * increase the available space by GUEST_LIST_INCREMENT_SIZE.  Returns a pointer to 
 * 'guestList'.  If 'guestList' has been resized, we update the int pointed to by 'n' to
 * store the new size of the array.  Note: because we potentially call realloc(), the 
 * pointer to 'guestList' that we return may point at a new address; existing pointers to
 * 'guestList' are invalidated by this call. */
char **addToGuestList(char *name, char *guestList[], int *n);

/* Adds the specified name to 'acceptedList' (an array of strings of size '*n').  'name'
 * will be added in the appropriate position to keep 'acceptedList' sorted.  Existing 
 * entries in the array will be shifted down to make room, if necessary.  If 
 * 'acceptedList' does not have any available space, we realloc() the array to increase 
 * the available space by ACCEPTED_LIST_INCREMENT_SIZE.  Returns a pointer to 
 * 'acceptedList'.  If 'acceptedList' has been resized, we update the int pointed to by 
 * 'n' to store the new size of the array.  Note: because we potentially call realloc(), 
 * the pointer to 'acceptedList' that we return may point at a new address; existing 
 * pointers to 'acceptedList' are invalidated by this call. */
char **addToAcceptedList(char *name, char *acceptedList[], int *n);


/* Helper function to read a line of input.  Clears any whitespace off of the input 
 * buffer, and then safely reads at most n-1 characters from stdin, and stores them in 
 * 's', followed by a '\0'.  Removes the trailing '\n' character, if present. */
void getLine(char s[], int n);


/*
 * Begin Changes Here.
 */

// Add any new function prototypes here 
int lastNonNullIndex (char *acceptedList[], int n);

bool validateEmptyGuestList(char *guestList[], int n);

bool isValidRow(char *list[], int n);

/*
 * End Changes Here.
 */
 


#ifndef MAIN_DISABLED /* Do *not* modify or delete this line of code; it is used by the auto-marker. */
int main(void)
{

    // Allocate our guest list and accepted list
    
    /* The current size of guestList.  This is the size of the array, not the number of spaces currently in use. */
    int guestListSize = GUEST_LIST_INITIAL_SIZE;  
    
    /* Our guest list, which is stored as an array of strings (i.e., array of char *). */
    char **guestList = malloc(guestListSize * sizeof(char *));
    
    /* The current size of acceptedList.  This is the size of the array, not the number of spaces currently in use. */
    int acceptedListSize = ACCEPTED_LIST_INITIAL_SIZE;    

    /* Our accepted list, which is stored as an array of strings (i.e., array of char *). */
    char **acceptedList = malloc(acceptedListSize * sizeof(char *));   
    
    /* The number of people who will be attending. */
    int numAttendees = 0;

    /* Holds the row number from the guest list */
    int rowNum;

    /* A pointer to the name we wish to add/ accept to the list */
    char *name;

    /* Validates whether a Guest List is empty or not*/
    bool isEmptyGuestList;

    /* Checks whether the row number entered is already empty */
    bool validRow;


    /*
     * Begin Changes Here (Step 1).
     */
        
    // Set every pointer in both of those lists to NULL
    int i, j;

    for (i = 0; i < guestListSize; i++)
    {
        guestList[i] = NULL;
    }      

    for (j = 0; j < acceptedListSize; j++)
    {
        acceptedList[j] = NULL;
    }
    
    /*
     * End Changes Here.
     */
     
    /* 
     * Begin pseudocode.  Make changes here for Steps 2, 3, 4, 5, 8, and 10 
     */
     
    //Allocate a buffer for the user's command and initialize it to ""
    char command[CMD_MAX_LENGTH] = "";

    while (strcmp(command, MENU_QUIT) != 0)
    {
        //Prompt for and read in a command from the user
        printf("Please enter a command: ");
        getLine(command, CMD_MAX_LENGTH + 1);

        if (strcmp(command, MENU_ADD) == 0)
        {
            //Prompt for a name
            name = getName();

            //Add it to the guest list
            guestList = addToGuestList(name, guestList, &guestListSize);

        }
        else if (strcmp(command, MENU_PRINT) == 0)
        {
            //Print out the guest list (with header and footer)
            printf("--- Guest  List ---\n");
            printList(guestList, guestListSize);
            printf("-------------------\n");

            //Print out the accepted list (with header and footer)
            printf("-- Accepted List --\n");
            printList(acceptedList, acceptedListSize);
            printf("-------------------\n");

            //Print out the number of attendees
            printf("Number of attendees: %d\n", numAttendees);
    
        }
        else if (strcmp(command, MENU_DELETE) == 0)
        {
            // Checks whether the guest list is empty or not
            isEmptyGuestList = validateEmptyGuestList(guestList, guestListSize);

            if (isEmptyGuestList)
            {
                printf("The guest list is already empty.\n");
            }

            else
            {
                //Print out the guest list
                printList(guestList, guestListSize);

                //Prompt for a row number
                rowNum = getValidRow(guestListSize);

                // Validates the row number entered is not empty
                validRow = isValidRow(guestList, rowNum);

                while (!validRow)
                {
                    printf("Invalid selection. That row is empty.\n");
                    rowNum = getValidRow(guestListSize);
                    validRow = isValidRow(guestList, rowNum);
                }
                
                //free() that string
                free(guestList[rowNum]);

                //Set that pointer to NULL to indicate an empty space
                guestList[rowNum] = NULL;
            }
            
        }
        else if (strcmp(command, MENU_ACCEPT) == 0)
        {
            // Checks whether the guest list is empty or not
            isEmptyGuestList = validateEmptyGuestList(guestList, guestListSize);

            if (isEmptyGuestList)
            {
                printf("The guest list is empty.\n");
            }

            else
            {
                //Print out the guest list
                printList(guestList, guestListSize);

                //Prompt for a row number
                rowNum = getValidRow(guestListSize);

                // Validates the row number entered is not empty
                validRow = isValidRow(guestList, rowNum);

                while (!validRow)
                {
                    printf("Invalid selection. That row is empty.\n");
                    rowNum = getValidRow(guestListSize);
                    validRow = isValidRow(guestList, rowNum);
                }

                //Prompt if there is an additional guest for this person
                bool isExtraGuest = getIsExtraGuest();

                if (!isExtraGuest)
                {
                    //Add one person to our number of attendees
                    numAttendees++;

                    //The name that we are going to add is what is stored in guestList
                    name = guestList[rowNum];
                }

                else
                {
                    //Add two people to the number of attendees
                    numAttendees += 2;

                    //Figure out how long a string we need to hold the name plus the text TEXT_PLUS_GUEST
                    int namePlusGuestStrlen = NAME_MAX_LENGTH + strlen(TEXT_PLUS_GUEST) + 1;

                    //Allocate a new string of that length
                    char *namePlusGuest = malloc(namePlusGuestStrlen * sizeof(char));

                    /*Copy in the existing name...
                     ... and add on the text TEXT_PLUS_GUEST*/
                    strncpy(namePlusGuest, guestList[rowNum], strlen(name) + 1);
                    strncat(namePlusGuest, TEXT_PLUS_GUEST, (namePlusGuestStrlen - 1) - strlen(namePlusGuest));

                    name = namePlusGuest;

                    //free() the old name string
                    free(guestList[rowNum]);
                }

                //Add the name (either the original or the newly modified version) to the accepted list
                acceptedList = addToAcceptedList(name, acceptedList, &acceptedListSize);

                //Remove the name from guestList
                guestList[rowNum] = NULL;
            }       
        }    

        else if (strcmp(command, MENU_QUIT) != 0)
        {
            //Print out "Unknown command."
            printf("Unknown command.\n");
        }
    }
        
     /* End Pseudocode.
     */
    


    /*
     * Begin Changes Here (Step 13).
     */
        
    // Cleanup the strings in each array...
        
    // ... and the arrays themselves

    for (i = 0; i < guestListSize; i++)
    {
        free(guestList[i]);
    }

    for (j = 0; j < acceptedListSize; j++)
    {
        free(acceptedList[j]);
    }

    free(guestList);
    free(acceptedList);

    /*
     * End Changes Here.
     */

    return 0;
}
#endif /* Do *not* modify or delete this line of code; it is used by the auto-marker. */


void printList(char *list[], int n)
{
    /*
     * Begin Changes Here (Step 4).
     */
    int i;

    for (i = 0; i < n; i++)
    {
        if (list[i] == NULL)
        {
            printf("%2d: [empty]\n", i);
        }

        else
        {
            printf("%2d: %s\n", i, list[i]);   
        }
    }    
    
    
    /*
     * End Changes Here.
     */
} 


int getValidRow(int maxRow)
{
    /*
     * Begin Changes Here (Step 9).
     */
    int rowNum;

    printf("Enter a row number between 0 and %d: ", maxRow - 1);
    scanf("%d", &rowNum);

    while(rowNum < 0 || rowNum >= maxRow)
    {
        printf("Invalid row number.\n");
        printf("Enter a row number between 0 and %d: ", maxRow - 1);
        scanf("%d", &rowNum);
    }

    return rowNum;

    /*
     * End Changes Here.
     */
}              


bool getIsExtraGuest(void)
{
    /*
     * Begin Changes Here (Step 11).
     */
    
    // Allocate a buffer to hold the user input
    char input[CMD_MAX_LENGTH + 1];
    
    // Keep prompting until we get a valid response
    while(1)
    {
        // Prompt for a response
        printf("Is there an additional guest? [yes/no]: ");
        getLine(input, CMD_MAX_LENGTH + 1);
        
        // If the answer is CMD_YES, then we want to return true
        if (strcmp(input, CMD_YES) == 0)
        {
            return true;
        }

        // If the answer is CMD_NO, then we want to return false
        else if (strcmp(input, CMD_NO) == 0)
        {
            return false;
        }        

        // Otherwise, it's an invalid response
        else
            printf("Invalid response.\n");
    }
    
    /*
     * End Changes Here.
     */
}


char *getName(void)
{
    /*
     * Begin Changes Here (Step 6).
     */
    
    // Allocate a buffer to hold the user input
    char input[NAME_MAX_LENGTH + 1];

    // Prompt for a name
    printf("Enter a name: ");
    getLine(input, NAME_MAX_LENGTH + 1);
    
    // Allocate a new array to hold the string
    char *name = malloc((strlen(input) + 1) * sizeof(char));
    
    // Copy the characters into the newly allocated string
    strncpy(name, input, strlen(input) + 1);
    
    return name;
    
    /*
     * End Changes Here.
     */
}


char **addToGuestList(char *name, char *guestList[], int *n)
{
    /*
     * Begin Changes Here (Step 7).
     */
    
    // Try and find the first NULL in the array.  If we find one, add the name in that location.
    int i;

    for (i = 0; i < *n; i++)
    {
        if (guestList[i] == NULL)
        {
            guestList[i] = name;
            return guestList;
        }
    }

    // If we weren't able to add the name, our array is full
    if (i == *n)
    {
        // Increase the size of the array
        *n += GUEST_LIST_INCREMENT_SIZE;

        guestList = realloc(guestList, *n * sizeof(char *));
        
        // Add the name to the first newly added index
        guestList[i] = name;

        // Set all of the rest of the newly added pointers to NULL
        for (i += 1; i < *n; i++)
        {
            guestList[i] = NULL;
        }

    }

    /*
     * End Changes Here.
     */
     
    return guestList;
}


char **addToAcceptedList(char *name, char *acceptedList[], int *n)
{

    /*
     * Begin Changes Here (Step 12).
     */
        
    // Figure out where to add the name to maintain the sorted order
    int i, j, position = -1;
    bool check = true;

    for (i = 0; i < *n; i++)
    {
        if (acceptedList[i] == NULL && check)
        {
            position = i;
            check = false;
        }

        else if (check && (strcmp(name, acceptedList[i]) < 0))
        {
            position = i;
            check = false;
        }
    }

    /* At this point, our position is pointing one element past where we want to add the name, 
       since we incremented it once before leaving the loop, so decrement it */
    if (position == -1)
    {
        position = i;
    }

    // Check if there are any empty spaces in the array.
    
    // If not, we need to enlarge it
    if(acceptedList[i - 1] != NULL)
    {   
        // Calculate the new size
        *n += ACCEPTED_LIST_INCREMENT_SIZE;
        
        // Resize the array
        acceptedList = realloc(acceptedList, *n * sizeof(char *));
        
        // Set each of the new pointers to NULL
        for (i += 0; i < *n; i++)
        {
            acceptedList[i] = NULL;
        }
    }   

    // Shift every element between the last index and the position that we're adding the name
    // This creates an empty space where we want to add the name
    // For simplicity, we just copy every pointer in those indices, including any NULL pointers.
    
    int lastIndex = lastNonNullIndex(acceptedList, *n);
    
    bool endOfList = false;

    for (i = 0; i < *n; i++)
    {
        if (acceptedList[i] == NULL && !endOfList)
        {
            acceptedList[position] = name;
            endOfList = true;
        }

        else if (!endOfList && (strcmp(name, acceptedList[i]) < 0))
        {
            for (j = lastIndex; j >= position; j--)
            {
                acceptedList[j + 1] = acceptedList[j];
                acceptedList[j] = NULL;
            }

            acceptedList[position] = name;
            endOfList = true;
        }
    }
    
    // Now that acceptedList[position] is empty, point that pointer to the name
    
    /*
     * End Changes Here.
     */   
      
    return acceptedList;
}


void getLine(char s[], int n)
{
    // Read any remaining whitespace off our stdin buffer, since we may be switching from scanf() to fgets(). 
    scanf(" ");
        
    // Read in our string
    fgets(s, n, stdin);
    
    // If the last character is a \n, strip it by replacing it with a \0
    if (s[strlen(s) - 1] == '\n')
    {
        s[strlen(s) - 1] = '\0';
    }
}



/*
 * Begin Changes Here.
 */
     
// Place any new helper functions here.
int lastNonNullIndex (char *acceptedList[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if(acceptedList[i] == NULL)
            return i - 1;
    }
}

bool validateEmptyGuestList(char *guestList[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if(guestList[i] != NULL)
            return false;
    }
    return true;
}

bool isValidRow(char *list[], int n)
{
    if (list[n] == NULL)
        return false;

    return true;
}

/*
 * End Changes Here.
 */ 
 
