// APS105 Assignment 5 Starter Code
// Jonathan Deber (deberjon) 991234567
// Sun 02 Jun 2015 03:06:33 PM EDT 

// This program helps solve a largest subset problem

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* The maximum number of numbers in our subsets. */
#define MAX_NUMBER_OF_NUMBERS 10

/* Yes and no responses. */
#define Y 'y'
#define N 'n'

/* Default number list to save typing. */
const int DEFAULT_NUMBERS[] = {1, 2, 4, 5, 8, 12, 15, 21};

/* Size of the default number list. */
const int NUM_DEFAULT_NUMBERS = sizeof(DEFAULT_NUMBERS) / sizeof(DEFAULT_NUMBERS[0]);

/* The struct used for the linked list Nodes. */
typedef struct node
{
    int numbers[MAX_NUMBER_OF_NUMBERS]; // The numbers that make up this subset
    int n;                              // The number of elements in 'numbers'
    
    struct node *next;                  // Pointer to the next node
} Node;


/* Node functions. */

/* Creates a new Node, and returns a pointer to it.
 * Copies 'n' and every value in 'numbers' into the equivalent fields in the new Node.
 * Sets the Node's 'next' pointer to NULL.
 * Nodes must be cleaned up with destroyNode(). 
 * Note: this function may be implemented iteratively. */
Node *createNode(const int numbers[], int n);

/* Cleans up the specified Node by free()ing any necessary fields, and then free()ing
 * the Node itself.  Does nothing if passed NULL. */
void destroyNode(Node *node);

/* Prints out the contents of the Node in the format specified in the assignment handout.
 * This function is used for debugging purposes, and is not used to print out the final answers. */
void debugPrintNode(const Node *node);

/* Returns the sum of all of the numbers in node->numbers.
 * Note: this function may be implemented iteratively. */
int calculateSumOfNode(const Node *node);



/* List functions. */

/* Creates a new Node containing 'numbers' and 'n', and adds it to the end of the linked 
 * list pointed to by 'head'.  Returns a pointer to the head of the list.  If 'head' is 
 * NULL, then we create a new list of size 1 (i.e., consisting entirely of the new Node we
 * just created), and return a pointer to that. 
 * Note: this function must be implemented recursively. */
Node *addNodeToList(Node *head, const int numbers[], int n);

/* Adds the linked list pointed to by 'head2' on to the end of the linked list pointed to by
 * 'head1'.  If 'head1' is NULL, returns 'head2'.  If 'head2' is NULL, then 'head1' is unchanged.
 * Note: this function must be implemented recursively. */
Node *addLists(Node *head1, Node *head2);

/* Prints out the list pointed to by 'head' in the format specified in the assignment handout. 
 * This function is used for debugging purposes, and is not used to print out the final answers.
 * Note: this function must be implemented recursively. */
void debugPrintList(const Node *head);

/* Prints out each set of numbers in the linked list pointed to by 'head', one per line.  This is used
 * to print out the final list of suggested subsets of numbers.
 * Note: this function must be implemented recursively. */
void printList(const Node *head);

/* Traverses the linked list pointed to by 'head', and determines the largest sum of the subset
 * in a Node that is less than or equal to 'targetValue'.
 * This function merely returns the sum, it does not return the subset itself.
 * Note: this function must be implemented recursively. */
int findHighestValidTotal(const Node *head, int targetValue);



/* Permutation functions. */

/* Generates all of the possible permutations (including permutations of 
 * shorter subsets) of the numbers in 'numbers' (which is of length 'n'), and returns them as a linked
 * list of Nodes.  The Nodes in the returned list must later be free()ed by
 * destroyNode(). */
Node *generatePermutations(const int numbers[], int n);

/* Generates all of the possible permutations that can be created by inserting 'number' 
 * into every element in the linked list pointed to by 'head', and returns
 * them as a new linked list. The Nodes in the returned list must later be free()ed
 * by destroyNode(). */ 
Node *insertIntoEveryElement(const Node *list, int number);




/*
 * Begin Changes Here.
 */
     
// Add any additional helper function prototypes or constants here.

void printNodeArray(const int numbers[], int n);

void debugDestroyList(Node *head);

Node *subsetsList(const Node *head, int highestValidTotal);

void destroyList(Node *head);

/*
 * End Changes Here.
 */



/* True to print out additional debugging info, false to suppress it. */
#define DEBUGGING false


#ifndef AUTOMARKER /* Do *not* modify or delete this line of code; it is used by the auto-marker. */
int main(void)
{   
    Node *head = NULL;
    Node *resultList = NULL;
    
    /* The available numbers we have to work with. */
    int availableNumbers[NUM_DEFAULT_NUMBERS];
    
    /* The number of numbers in that array. */
    int numAvailableNumbers;
   
    // Ask the user if we want to use the default numbers
    char response;
        
    do
    {
        printf("Use default set of numbers? [y/n] ");
        scanf(" %c", &response);
    } while (response != Y && response != N);
    
    // If so, copy in the default set
    if (response == Y)
    {
        int i;
        for (i = 0; i < NUM_DEFAULT_NUMBERS; i++)
        {
            availableNumbers[i] = DEFAULT_NUMBERS[i];
        }
        numAvailableNumbers = NUM_DEFAULT_NUMBERS;
    }

    // Otherwise, prompt the user for numbers
    else
    {
        int number = 0;
        numAvailableNumbers = 0;
        
        int i;
        for (i = 0; i < MAX_NUMBER_OF_NUMBERS && number != -1; i++)
        {
            printf("Enter a number (-1 to exit): ");
            scanf("%d", &number);
            
            if (number != -1)
            {
                availableNumbers[i] = number;
                numAvailableNumbers++;
            }
        }
    }

    // Prompt the user for a target value    
    int targetValue;
    printf("Enter target value: ");
    scanf("%d", &targetValue);
    
    /*
     * Begin Changes Here (Steps 10, 11, 12, 13, 14).
     */
        
    // Generate the set of possible permutations.
    head = generatePermutations(availableNumbers, numAvailableNumbers);
    
    // Get the highest total less than or equal to targetValue.
    int highestValidTotal = findHighestValidTotal(head, targetValue);

    // Filter the list of permutations to get the subsets with that total.
    resultList = subsetsList(head, highestValidTotal);
    
    // Print out those filtered subsets
    printList(resultList);

    // Clean up
    destroyList(resultList);
    destroyList(head);
    
    resultList = NULL;
    head = NULL;
    /*
     * End Changes Here.
     */

    return 0;
}
#endif /* Do *not* modify or delete this line of code; it is used by the auto-marker. */



Node *createNode(const int numbers[], int n)
{
    /*
     * Begin Changes Here (Step 2).
     */   

    Node *newNode = malloc(sizeof(Node));
    
    int i;
    for (i = 0; i < n; ++i)
    {
        newNode->numbers[i] = numbers[i];
    } 

    newNode->n = n;
    
    return newNode; 
        
    /*
     * End Changes Here.
     */ 
}

void destroyNode(Node *node)
{
    /*
     * Begin Changes Here (Step 2).
     */

    free(node);
    
    /*
     * End Changes Here.
     */ 
}

void debugPrintNode(const Node *node)
{
    /*
     * Begin Changes Here (Step 3).
     */

    if (node == NULL)
    {
        printf("  [null]\n");
    }

    else
    {
        printf("----------\n");
        printf("Numbers: ");
        printNodeArray(node->numbers, node->n);
        printf("n: %d\n", node->n);
        printf("----------\n");
    }

    
    /*
     * End Changes Here.
     */
}


int calculateSumOfNode(const Node *node)
{
    /*
     * Begin Changes Here (Step 11).
     */
    
    int sum = 0;
    
    int i;
    for (i = 0; i < node->n; ++i)
    {
        sum += node->numbers[i];
    }
    
    return sum;  // REPLACE THIS LINE
    
    /*
     * End Changes Here.
     */
}



Node *addNodeToList(Node *head, const int numbers[], int n)
{
    /*
     * Begin Changes Here (Step 5).
     */

    if (head == NULL)
    {
        head = createNode(numbers, n);
        head->next = NULL;
    }

    else
        head->next = addNodeToList(head->next, numbers, n);

    return head;
    
    /*
     * End Changes Here.
     */
}

Node *addLists(Node *head1, Node *head2)
{
    /*
     * Begin Changes Here (Step 6).
     */

    if (head1 == NULL)
    {
        return head2;
    }

    else
        head1->next = addLists(head1->next, head2);

    return head1; 
      
    /*
     * End Changes Here.
     */
}


void debugPrintList(const Node *head)
{
    /*
     * Begin Changes Here (Step 4).
     */

    if (head == NULL)
    {
        debugPrintNode(head);
    }

    else
    {
        debugPrintNode(head);
        printf("    |\n    v\n");
        debugPrintList(head->next);
    }
        
    /*
     * End Changes Here.
     */
     
}

void printList(const Node *head)
{
    /*
     * Begin Changes Here (Step 13).
     */

    printf("The subset(s) closest to the target value are:\n");

    while(head != NULL)
    {

        int i;
        for (i = 0; i < head->n; ++i)
        {
            printf("%d ", head->numbers[i]);
        }

        head = head->next;
        printf("\n");
    }        

    /*
     * End Changes Here.
     */
}


int findHighestValidTotal(const Node *head, int targetValue)
{
    /*
     * Begin Changes Here (Step 11).
     */

    // If the list is empty, our sum is 0
    int sumNode, largest;
    bool isRange;

    if (head == NULL)
    {
        largest = 0;
    }
    
    // Otherwise
    else
    {
        // Calculate the sum of this node
        sumNode = calculateSumOfNode(head);
        
        // Is it in range?
        isRange = sumNode <= targetValue;

        // Calculate the largest valid sum in the rest of the list        
        largest = findHighestValidTotal(head->next, targetValue);
        
        // Is that bigger than this Node's sum?  
        if (isRange)
        {
            if (sumNode == targetValue)
            {
                largest = sumNode;
            }
            
            else if (sumNode > largest && sumNode < targetValue)
            {
                largest = sumNode;
            }

            else
                ;
        }
    }

    return largest;  // REPLACE THIS LINE
    
    /*
     * End Changes Here.
     */
}



Node *generatePermutations(const int numbers[], int n)
{
    /*
     * Begin Changes Here (Step 8).
     */
     
    // Print out some information about the function call
    // (This debugging info may be printed iteratively)
    if (DEBUGGING)
    {

    }
    
    /* Create a linked list to hold our permutations. */
    Node *result = NULL;
    Node *list = NULL;
    
    // If we're down to a single number, add it as a 1-item subset and stop recursing.
    if (n == 1)
    {
        result = createNode(numbers, n);
    }

    
    // Otherwise
    else
    {
        // Take off the first number.
        numbers++;
        n--;
        
        // Generate all of the permutations of the smaller subset.
        result = generatePermutations(numbers, n);
        
        // Insert the removed number into every subset in that list.
        numbers--;
        list = insertIntoEveryElement(result, numbers[0]);
        
        // Add on the subsets we obtained from the recursive call.
        result = addLists(result, list);
        
        // Add on a subset containing our single number.
        result = addNodeToList(result, numbers, 1);

    }
    return result;  
    
    /*
     * End Changes Here.
     */
}

Node *insertIntoEveryElement(const Node *head, int number)
{    
    /*
     * Begin Changes Here (Step 9).
     */
         
    // Print out some information about the function call
    // (This debugging info may be printed iteratively)
    if (DEBUGGING)
    {

    }
    
    
    // As long as there are still Nodes in the list, keep processing.
    Node *newHead;

    if (head == NULL)
    {
        return head;
    }

    else
    {
        // Create a new Node with the existing numbers and the single number.
        int numArray[MAX_NUMBER_OF_NUMBERS];
        newHead = NULL;
        
        int i;
        for (i = 0; i <= head->n; i++)
        {
            if (i == head->n)
            {
                numArray[i] = number;
            }

            else
                numArray[i] = head->numbers[i];
        }

        newHead = createNode(numArray, head->n + 1);
        newHead->next = NULL;

        // Recursively generate all of the insertions for the remaining Nodes.
        newHead->next = insertIntoEveryElement(head->next, number);
    }

    return newHead;  // REPLACE THIS LINE
    
    /*
     * End Changes Here.
     */
}







/*
 * Begin Changes Here.
 */
     
// Place any new helper functions here.

void printNodeArray(const int numbers[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
    {
        printf("%d ", numbers[i]);
    }

    printf("\n");
}

void debugDestroyList(Node *head)
{
    Node *p, *next;
    
    for (p = head; p != NULL; p = next) 
    {
        next = p->next;
        destroyNode(p);
    }
}

Node *subsetsList(const Node *head, int highestValidTotal)
{
    Node *list = NULL;
    int sumNode, numArray[MAX_NUMBER_OF_NUMBERS];

    while(head != NULL)
    {
        sumNode = calculateSumOfNode(head);

        if (sumNode == highestValidTotal)
        {
            int i;
            for (i = 0; i < head->n; i++)
            {
               numArray[i] = head->numbers[i];
            }

            list = addNodeToList(list, numArray, head->n);
        }

        else
            ;
        head = head->next;
    }

    return list;
}

void destroyList(Node *head)
{
    Node *tmp;

    if (head != NULL)
    {
        tmp = head->next;
        destroyNode(head);
        head = tmp;
        destroyList(head);
    }
}


/*
 * End Changes Here.
 */ 
