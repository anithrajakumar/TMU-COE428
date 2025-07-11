/**
 * The functions in this module implement a Stack data structure
 * of char pointers (aka "strings").
 *
 * NOTE: the stack is implemented as a fixed size array (size = 100).
 * Consequently, no more than 100 strings can be pushed onto
 * the Stack at any given time.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int stackTopIndex = 0;
static char * stringStack[100];

/**
 * pop() removes the top string on the stack and returns it.
 *
 * If pop() is attempted on an empty stack, an error message
 * is printed to stderr and the value NULL ((char *) 0) is returned.
 */
char * pop()
{
    if (stackTopIndex <= 0) {
        fprintf(stderr, "Stack Underflow: Cannot pop from empty stack\n");
        return NULL;
    }

    // Get top item and clear its position
    stackTopIndex--;
    char *poppedString = stringStack[stackTopIndex];
    stringStack[stackTopIndex] = NULL;
    
    return poppedString;
}

/**
 * push(thing2push) adds the "thing2push" to the top of the stack.
 *
 * If there is no more space available on the Stack, an error
 * message is printed to stderr.
 */
void push(char *stringToPush)
{
    // Validate stack capacity
    if (stackTopIndex >= 100) {
        fprintf(stderr, "Stack Overflow: Maximum capacity reached\n");
        return;
    }

    // Validate input
    if (stringToPush == NULL) {
        fprintf(stderr, "Error: Cannot push NULL string pointer\n");
        return;
    }

    // Create and verify string copy
    char *stringCopy = strdup(stringToPush);
    if (stringCopy == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for string\n");
        return;
    }

    // Add to stack and increment top index
    stringStack[stackTopIndex] = stringCopy;
    stackTopIndex++;
}

/**
 * isEmpty() returns a non-zero integer (not necessarily 1) if the
 * stack is empty; otherwise, it returns 0 (zero).
 */
int isEmpty()
{
    return stackTopIndex == 0;
}